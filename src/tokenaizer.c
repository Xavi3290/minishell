/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:05:46 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/29 19:45:19 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*handle_single_quotes(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*value;
	t_token	*token;

	(*i)++;
	start = (*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] != '\'')
	{
		handle_error("syntax error: unmatched '", shell);
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	token = new_token(SINGLE_QUOTES, value);
	return (token);
}

static t_token	*handle_double_quotes(char *line, int *i, t_shell *shell)
{
	int		start;
	char	*value;
	t_token	*token;

	(*i)++;
	start = (*i)++;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] != '"')
	{
		handle_error("syntax error: unmatched '", shell);
		return (NULL);
	}
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	token = new_token(DOUBLE_QUOTES, value);
	return (token);
}

static t_token	*handle_special_tokens(char *line, int *i)
{
	if (line[*i] == '(')
        return create_basic_token(LPAREN, "(", i);
    else if (line[*i] == ')')
        return create_basic_token(RPAREN, ")", i);
    else if (line[*i] == '|' && line[*i + 1] == '|')
        return create_basic_token(OR, "||", i);
    else if (line[*i] == '|')
        return create_basic_token(PIPE, "|", i);
    else if (line[*i] == '&' && line[*i + 1] == '&')
        return create_basic_token(AND, "&&", i);
    return NULL;
}

static t_token	*get_next_token(char *line, int *i, t_shell *shell)
{
	t_token	*token;

	token = handle_special_tokens(line, i);
	if (token)
		return (token);	
	if (line[*i] == '<' && line[*i + 1] == '<')
		token = create_basic_token(HEREDOC, "<<", i);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		token = create_basic_token(APPEND, ">>", i);
	else if (line[*i] == '<')
		token = create_basic_token(REDIRECT_IN, "<", i);
	else if (line[*i] == '>')
		token = create_basic_token(REDIRECT_OUT, ">", i);
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

/*int main(int argc, char **argv)
{
    char *line;
	int i;
	t_shell *shell;
	
	shell = init_shell(argv);
	i = argc;
	line = argv[1];
    t_token *token = tokenize(line, shell);
	t_token *temp = token;
	while (temp)
	{
		printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
		temp = temp->next;
	}

    return 0;
}*/
