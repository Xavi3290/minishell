/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/10 16:14:35 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	generate_random_number(void)
{
	static unsigned int	seed;

	seed = 12345;
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return (seed % 10000);
}

char	*generate_filename(void)
{
	char	*str;
	char	*num;

	num = ft_itoa(generate_random_number());
	str = ft_strjoin("hdoc_tmp_file", num);
	free(num);
	return (str);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->num_args = 0;
	cmd->input_files = NULL;
	cmd->output_files = NULL;
	cmd->append_output = 0;
	cmd->heredoc = 0;
	cmd->and = 0;
	cmd->or = 0;
	cmd->parentheses = 0;
	cmd->fd = -1;
	cmd->next = NULL;
	return (cmd);
}

void	add_argument(t_command *cmd, char *arg)
{
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * cmd->num_args, \
				sizeof(char *) * (cmd->num_args + 2));
	cmd->args[cmd->num_args] = ft_strdup(arg);
	cmd->num_args++;
	cmd->args[cmd->num_args] = NULL;
}

void	add_input_file(t_command *cmd, char *file)
{
	int	i;

	i = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
}

void	add_output_file(t_command *cmd, char *file, int append)
{
	int	i;

	i = 0;
	while (cmd->output_files && cmd->output_files[i])
		i++;
	cmd->output_files = ft_realloc(cmd->output_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->output_files[i] = ft_strdup(file);
	cmd->output_files[i + 1] = NULL;
	cmd->append_output = append;
}

void	add_heredoc_file(t_command *cmd, char *file)
{
	int	i;

	i = 0;
	while (cmd->input_files && cmd->input_files[i])
		i++;
	cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, \
						sizeof(char *) * (i + 2));
	cmd->input_files[i] = ft_strdup(file);
	cmd->input_files[i + 1] = NULL;
	cmd->heredoc = 1;
}

void	handle_redirect_token(t_token **current, t_command *cmd, \
		t_shell *shell, int type)
{
	*current = (*current)->next;
	while (*current && (*current)->type == SPACES)
		*current = (*current)->next;
	if (*current && (*current)->type == WORD)
	{
		if (type == REDIRECT_IN)
			add_input_file(cmd, (*current)->value);
		else if (type == REDIRECT_OUT)
			add_output_file(cmd, (*current)->value, 0);
		else if (type == APPEND)
			add_output_file(cmd, (*current)->value, 1);
	}
	else
		handle_error("syntax error: expected file after redirection", shell);
}

void	handle_heredoc_token(t_command *cmd)
{
	char	*filename;

	filename = generate_filename();
	add_heredoc_file(cmd, filename);
	free(filename);
}

void	handle_pipe_token(t_command **cmd)
{
	(*cmd)->next = create_command();
	*cmd = (*cmd)->next;
}

void	handle_logical_token(t_token *current, t_command **cmd)
{
	if (current->type == AND)
		(*cmd)->and = 1;
	else
		(*cmd)->or = 1;
	(*cmd)->next = create_command();
	*cmd = (*cmd)->next;
}

void	handle_left_parenthesis(t_command **cmd, int *paren_level)
{
	(*paren_level)++;
	if ((*cmd)->num_args > 0 || (*cmd)->input_files || (*cmd)->output_files)
	{
		(*cmd)->next = create_command();
		*cmd = (*cmd)->next;
	}
	(*cmd)->parentheses = *paren_level;
}

void	handle_right_parenthesis(t_command **cmd, int *paren_level)
{
	if (*paren_level > 0)
	{
		(*cmd)->next = create_command();
		*cmd = (*cmd)->next;
		(*cmd)->parentheses = *paren_level;
		(*paren_level)--;
	}
}

void	parse_general_tokens_cmd(t_token **tokens, t_command *cmd, \
		t_shell *shell, int *paren_level)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == WORD || current->type == DOUBLE_QUOTES || \
			current->type == SINGLE_QUOTES || current->type == WILDC)
			add_argument(cmd, current->value);
		else if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT \
				|| current->type == APPEND)
			handle_redirect_token(&current, cmd, shell, current->type);
		else if (current->type == HEREDOC)
			handle_heredoc_token(cmd);
		else if (current->type == PIPE)
			handle_pipe_token(&cmd);
		else if (current->type == AND || current->type == OR)
			handle_logical_token(current, &cmd);
		else if (current->type == LPAREN)
			handle_left_parenthesis(&cmd, paren_level);
		else if (current->type == RPAREN)
			handle_right_parenthesis(&cmd, paren_level);
		current = current->next;
	}
	*tokens = current;
}

void	parse_tokens(t_token **tokens, t_shell *shell)
{
	t_command	*current_cmd;
	int			paren_level;

	paren_level = 0;
	current_cmd = create_command();
	shell->commands = current_cmd;
	parse_general_tokens_cmd(tokens, current_cmd, shell, &paren_level);
}
