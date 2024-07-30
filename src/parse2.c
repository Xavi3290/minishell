/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:05:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/30 16:42:47 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	generate_random_number(void)
{
	static unsigned int	seed;
	
	if (seed == 0)
		seed = 12345;
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return (seed % 10000);
}

static char	*generate_filename(void)
{
	char	*str;
	char	*num;

	num = ft_itoa(generate_random_number());
	str = ft_strjoin("hdoc_tmp_file", num);
	free(num);
	return (str);
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

void	handle_heredoc_token(t_command *cmd, t_token **current)
{
	char	*filename;

	filename = generate_filename();
	*current = (*current)->next;
	while (*current && (*current)->type == SPACES)
		*current = (*current)->next;
	add_heredoc_file(cmd, filename, (*current)->value, (*current)->type);
	free(filename);
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
