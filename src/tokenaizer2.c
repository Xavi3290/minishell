/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:02:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/28 19:32:22 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(t_token_type type, char *value)
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

void	free_tokens(t_token *tokens)
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

t_token	*create_basic_token(char type, char *value, int *i, int plus)
{
	if (plus)
		(*i)++;
	return (new_token(type, ft_strdup(value)));
}
