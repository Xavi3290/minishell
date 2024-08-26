/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:50 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/26 16:09:09 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*strings_to_tokens(char **strings)
{
	t_token	*tokens;
	t_token	*new_tok;
	int		i;

	tokens = NULL;
	i = 0;
	while (strings[i])
	{
		new_tok = new_token(WILDC, ft_strdup(strings[i]));
		if (!new_tok)
			return (NULL);
		add_token(&tokens, new_tok);
		i++;
	}
	return (tokens);
}

void	insert_tokens(t_token **tokens, t_token *new_tokens, t_token *prev,
		t_token *current)
{
	t_token	*last_new;

	if (!new_tokens)
		return ;
	last_new = new_tokens;
	while (last_new->next)
		last_new = last_new->next;
	if (prev)
		prev->next = new_tokens;
	else
		*tokens = new_tokens;
	last_new->next = current->next;
	free(current->value);
	free(current);
}

char	*handle_dollar_signs(char *str, int i)
{
	int		dollar_count;
	char	*dollar_str;
	char	*dup;

	dollar_count = 0;
	if (!str)
		return (ft_strdup(""));
	while (str[i] == '$')
	{
		dollar_count++;
		i++;
	}
	if (dollar_count > 1)
	{
		dollar_str = malloc(dollar_count);
		if (!dollar_str)
			return (NULL);
		memset(dollar_str, '$', dollar_count - 1);
		dollar_str[dollar_count - 1] = '\0';
		dup = ft_strdup(dollar_str);
		free(dollar_str);
		return (dup);
	}
	return (ft_strdup(""));
}

void	join_adjacent_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current && current->next)
	{
		next = current->next;
		if (next->type == WORD || next->type == DOUBLE_QUOTES || \
			next->type == SINGLE_QUOTES)
		{
			if (current->type == WORD || current->type == DOUBLE_QUOTES \
				|| current->type == SINGLE_QUOTES || current->type == DELIMITER
				|| current->type == WILDC)
			{
				join_token_values(current, next);
				continue ;
			}
		}
		current = current->next;
	}
}

void	remove_empty_token(t_token **tokens, t_token **current, t_token **prev)
{
	t_token	*temp;

	temp = *current;
	if (*prev)
		(*prev)->next = (*current)->next;
	else
		*tokens = (*current)->next;
	*current = (*current)->next;
	free(temp->value);
	free(temp);
}
