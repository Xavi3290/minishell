/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:02:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 15:04:16 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		handle_error(NULL, NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
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

t_token	*create_basic_token(char type, char *value, int *i, t_shell *shell)
{
	char	*val;
	t_token	*token;

	if (!ft_strcmp(value, ">>") || !ft_strcmp(value, "<<") || !ft_strcmp(value,
			"&&") || !ft_strcmp(value, "||"))
		(*i)++;
	val = ft_strdup(value);
	if (!val)
		handle_error(NULL, NULL);
	token = new_token(type, val);
	if (token->type == HEREDOC)
		shell->heredoc = 1;
	return (token);
}

t_token	*handle_space(const char *line, int *i, t_shell *shell)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t'
			|| line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r'))
		(*i)++;
	(*i)--;
	return (create_basic_token(SPACES, " ", i, shell));
}
