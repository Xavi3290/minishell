/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:05:46 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/28 19:48:32 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*handle_quotes(char *line, int *i, int single)
{
	int		start;
	char	*value;
	t_token	*token;

	(*i)++;
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
	(*i)--;
	return (token);
}

static t_token	*handle_space(const char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t'
			|| line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r'))
		(*i)++;
	(*i)--;
	return (create_basic_token(SPACES, " ", i, 0));
}

static t_token	*get_next_token(char *line, int *i)
{
	t_token	*token;

	if (line[*i] == '|' && line[*i + 1] == '|')
		token = create_basic_token(OR, "||", i, 1);
	else if (line[*i] == '|')
		token = create_basic_token(PIPE, "|", i, 0);
	else if (line[*i] == '&' && line[*i + 1] == '&')
		token = create_basic_token(AND, "&&", i, 1);
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
	else if (ft_is_space(line[*i]))
		token = handle_space(line, i);
	else
		token = handle_word(line, i);
	return (token);
}

t_token	*tokenize(char *line)
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

/*int main(int argc, char **argv)
{
    char *line;
	int i;

	i = argc;
	line = argv[1];
    t_token *token = tokenize(line);
	t_token *temp = token;
	while (temp)
	{
		printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
		temp = temp->next;
	}

    return 0;
}*/
