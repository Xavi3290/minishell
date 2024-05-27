/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:05:46 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/27 19:02:32 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new_token;
}

static void	free_tokens(t_token *tokens)
{
	t_token	*token;
	t_token	*next;

	token = tokens;
	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

/*t_token *tokenize(char *line)
{
	t_token	*tokens;
	t_token	*token;
	char	*value;
	int		i;
	int		j;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			token = new_token(PIPE, ft_strdup("|"));
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			token = new_token(HEREDOC, ft_strdup("<<"));
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			token = new_token(APPEND, ft_strdup(">>"));
			i++;
		}
		else if (line[i] == '<')
			token = new_token(REDIRECT_IN, ft_strdup("<"));
		else if (line[i] == '>')
			token = new_token(REDIRECT_OUT, ft_strdup(">"));
		else if (line[i] == '\'')
		{
			i++;
			j = i;
			while (line[i] && line[i] != '\'')
				i++;
			value = ft_strndup(&line[j], i - j);
			token = new_token(WORD, value);
			free(value);
			if  (line[i] == '\'')
				i++;
			else
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
		else if (line[i] == '"')
		{
			i++;
			j = i;
			while (line[i] && line[i] != '"')
				i++;
			value = ft_strndup(&line[j], i - j);
			token = new_token(WORD, value);
			free(value);
			if (line[i] == '"')
				i++;
			else
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
		else if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t'
			|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		{
			token = new_token(SPACE, ft_strdup(" "));
			i++;
		}
		else
		{
			j = i;
			while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<'
				&& line[i] != '>' && line[i] != '\'' && line[i] != '"')
				i++;
			value = ft_strndup(&line[j], i - j);
			token = new_token(WORD, value);
			free(value);
			i--;
		}
		add_token(&tokens, token);
		i++;
	}
	return (tokens);
}*/
static t_token	*create_basic_token(char type, char *value, int *i, int plus)
{
	if (plus)
		(*i)++;
	return (new_token(type, ft_strdup(value)));
}

static t_token	*handle_quotes(char *line, int *i, int single)
{
	int		start;
	char	*value;
	t_token	*token;

	start = (*i)++;
	if (single)
	{
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] != '\'')
			return (NULL);
	}
	else
	{
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (line[*i] != '"')
			return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	token = new_token(WORD, value);
	free(value);
	(*i)++;
	return (token);
}

static t_token	*handle_word(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '|' && line[*i] != '<'
		&& line[*i] != '>' && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	value = ft_strndup(&line[start], *i - start);
	token = new_token(WORD, value);
	free(value);
	(*i)--;
	return (token);
}

static t_token	*handle_space(const char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t'
			|| line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r'))
		(*i)++;
	return (create_basic_token(SPACE, " ", i, 0));
}

static t_token	*get_next_token(const char *line, int *i)
{
	t_token	*token;

	if (line[*i] == '|')
		token = create_basic_token(PIPE, "|", i, 0);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		token = create_basic_token(HEREDOC, "<<", i, 1);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		token = create_basic_token(APPEND, ">>", i, 1);
	else if (line[*i] == '<')
		token = create_basic_token(REDIRECT_IN, "<", i, 0);
	else if (line[*i] == '>')
		token = create_basic_token(REDIRECT_OUT, ">", i, 0);
	else if (line[*i] == '\'')
		token = handle_quotes(line, i, 1);
	else if (line[*i] == '"')
		token = handle_quotes(line, i, 0);
	else if (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t'
		|| line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		token = handle_space(line, i);
	else
		token = handle_word(line, i);
	return (token);
}

static t_token	*tokenize(char *line)
{
	t_token	*tokens;
	t_token	*token;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		token = get_next_token(line, &i);
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
