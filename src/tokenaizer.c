/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:05:46 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/08 17:01:35 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*handle_single_quotes(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*value;

	(*i)++;
	start = (*i);
	if (line[*i] == '\'')
		return (new_token(SINGLE_QUOTES, ft_strdup("\0")));
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\0')
	{
		handle_errors("syntax error: unmatched '", shell, 2);
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	return (new_token(SINGLE_QUOTES, value));
}

static t_token	*handle_double_quotes(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*value;

	(*i)++;
	start = (*i);
	if (line[*i] == '"')
		return (new_token(DOUBLE_QUOTES, ft_strdup("\0")));
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] == '\0')
	{
		handle_errors("syntax error: unmatched '", shell, 2);
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	return (new_token(DOUBLE_QUOTES, value));
}

static t_token	*handle_special_tokens(char *line, int *i)
{
	if (line[*i] == '|' && line[*i + 1] == '|')
		return (create_basic_token(OR, "||", i));
	else if (line[*i] == '|')
		return (create_basic_token(PIPE, "|", i));
	else if (line[*i] == '&' && line[*i + 1] == '&')
		return (create_basic_token(AND, "&&", i));
	if (line[*i] == '<' && line[*i + 1] == '<')
		return (create_basic_token(HEREDOC, "<<", i));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return (create_basic_token(APPEND, ">>", i));
	else if (line[*i] == '<')
		return (create_basic_token(REDIRECT_IN, "<", i));
	else if (line[*i] == '>')
		return (create_basic_token(REDIRECT_OUT, ">", i));
	return (NULL);
}

static t_token	*get_next_token(char *line, int *i, t_shell *shell)
{
	t_token	*token;

	token = handle_special_tokens(line, i);
	if (token)
		return (token);
	if (line[*i] == '(')
		token = handle_left_parentheses(line, i, shell);
	else if (line[*i] == ')')
		token = handle_right_parentheses(shell, i);
	else if (line[*i] == '\'')
		token = handle_single_quotes(line, i, shell);
	else if (line[*i] == '"')
		token = handle_double_quotes(line, i, shell);
	else if (ft_is_space(line[*i]))
		token = handle_space(line, i);
	else
		token = handle_word(line, i);
	return (token);
}

t_token	*tokenize(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		token = get_next_token(line, &i, shell);
		if (!token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token(&tokens, token);
		i++;
	}
	return (tokens);
}
