/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:19:21 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/12 13:40:14 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_word(char *line, int *i)
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
	token = new_token(WORD, value);
	(*i)--;
	return (token);
}

int	handle_end_quotes(int *i, char *line, t_shell *shell, char c)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (line[j])
	{
		if (line[j] == c)
			count++;
		j++;
	}
	if (count % 2 != 0)
	{
		handle_error("syntax error: unmatched '", shell);
		return (0);
	}
	return (count);
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
				handle_error("syntax error: unmatched )", shell);
				return (NULL);
			}
			j++;
		}
		shell->parentheses = 1;
	}
	token = create_basic_token(LPAREN, "(", i);
	return (token);
}

t_token	*handle_right_parentheses(t_shell *shell, int *i)
{
	if (!shell->parentheses)
	{
		handle_error("syntax error: unmatched )", shell);
		return (NULL);
	}
	else
		return (create_basic_token(RPAREN, ")", i));
}
