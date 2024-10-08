/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_and_parentheses.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:19:21 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 15:11:59 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_word(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '|' && line[*i] != '<'
		&& line[*i] != '>' && line[*i] != '(' && line[*i] != ')'
		&& line[*i] != '"' && line[*i] != '\'')
	{
		if (line[*i] == '&' && line[*i + 1] == '&')
			break ;
		(*i)++;
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	if (shell->heredoc)
		token = new_token(DELIMITER, value);
	else
		token = new_token(WORD, value);
	shell->heredoc = 0;
	(*i)--;
	return (token);
}

t_token	*handle_left_parentheses(char *line, int *i, t_shell *shell)
{
	int		j;
	int		count;
	t_token	*token;

	if (!shell->parentheses)
	{
		j = (*i);
		count = 0;
		while (line[j])
		{
			if (line[j] == '(')
				count++;
			if (line[j] == ')')
				count--;
			if (count < 0)
			{
				handle_errors("syntax error: unmatched )", shell, 2);
				return (NULL);
			}
			j++;
		}
		shell->parentheses = 1;
	}
	token = create_basic_token(LPAREN, "(", i, shell);
	return (token);
}

t_token	*handle_right_parentheses(t_shell *shell, int *i)
{
	if (!shell->parentheses)
	{
		handle_errors("syntax error: unmatched )", shell, 2);
		return (NULL);
	}
	else
		return (create_basic_token(RPAREN, ")", i, shell));
}
