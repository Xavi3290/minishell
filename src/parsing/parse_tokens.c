/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 16:19:48 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_left_parenthesis(t_command **cmd, int *paren_level)
{
	(*paren_level)++;
	if ((*cmd)->num_args > 0 || (*cmd)->input_files || (*cmd)->output_files)
	{
		(*cmd)->next = create_command();
		*cmd = (*cmd)->next;
	}
	(*cmd)->parentheses = *paren_level;
}

static void	handle_right_parenthesis(t_command **cmd, int *paren_level)
{
	if (*paren_level > 0)
	{
		(*cmd)->next = create_command();
		*cmd = (*cmd)->next;
		(*cmd)->parentheses = *paren_level;
		(*paren_level)--;
	}
}

void	parse_general_tokens_cmd(t_token **tokens, t_command *cmd,
		t_shell *shell, int *paren_level)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type == WORD || current->type == DOUBLE_QUOTES \
			|| current->type == SINGLE_QUOTES || current->type == WILDC \
			|| current->type == DELIMITER)
			add_argument(cmd, current->value);
		else if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT
			|| current->type == APPEND)
			handle_redirect_token(&current, cmd, shell, current->type);
		else if (current->type == HEREDOC)
			handle_heredoc_token(cmd, &current);
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
}

void	handle_redirections(t_token **tokens, t_shell *shell)
{
	t_token	*current;

	current = *tokens;
	if (shell->last_exit_status == 130)
		return ;
	while (current)
	{
		if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT \
			|| current->type == APPEND)
			process_redirection_file(&current, shell, current->type);
		else if (current->type == PIPE)
			shell->flag_redirects = 2;
		current = current->next;
	}
}

void	parse_tokens(t_token **tokens, t_shell *shell)
{
	t_command	*current_cmd;
	int			paren_level;
	t_command	*tmp;

	paren_level = 0;
	current_cmd = create_command();
	shell->commands = current_cmd;
	parse_general_tokens_cmd(tokens, current_cmd, shell, &paren_level);
	tmp = current_cmd;
	while (tmp)
	{
		if (tmp->heredoc)
		{
			process_heredocs(shell, tmp);
			if (shell->last_exit_status == 130)
			{
				shell->flag_redirects = 0;
				break ;
			}
		}
		tmp = tmp->next;
	}
	handle_redirections(tokens, shell);
}
