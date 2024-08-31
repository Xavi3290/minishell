/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:23:12 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/31 11:26:33 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_variable_token(t_token **tokens, t_shell *shell,
		t_token **current, t_token **prev)
{
	char	*expanded;
	t_token	*new_tokens;

	expanded = expand_variable((*current)->value, shell);
	if (expanded && expanded[0] != '\0')
	{
		new_tokens = tokenize(expanded, shell);
		insert_tokens(tokens, new_tokens, *prev, *current);
		if (*prev)
			*current = (*prev)->next;
		else
			*current = *tokens;
		free(expanded);
	}
	else
	{
		remove_empty_token(tokens, current, prev);
		free(expanded);
	}
}

static void	expand_double_quotes_token(t_token *current, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(current->value, shell);
	if (expanded)
	{
		free(current->value);
		current->value = expanded;
	}
	else
	{
		free(current->value);
		current->value = ft_strdup("");
	}
}

static void	handle_wildcard_expansion(t_token **tokens, t_shell *shell,
		t_token **current, t_token **prev)
{
	join_adjacent_tokens(tokens);
	expand_wildcard_token(tokens, shell, current, prev);
	*prev = *current;
	*current = (*current)->next;
}

void	expand_tokens(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD && ft_strchr(current->value, '$'))
			expand_variable_token(tokens, shell, &current, &prev);
		else if (current->type == DOUBLE_QUOTES && ft_strchr(current->value,
				'$'))
		{
			expand_double_quotes_token(current, shell);
			prev = current;
			current = current->next;
		}
		else if (current->type == WORD && ft_strchr(current->value, '*'))
			handle_wildcard_expansion(tokens, shell, &current, &prev);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

t_token	*tokenize_and_expand(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = tokenize(line, shell);
	if (!tokens)
		return (NULL);
	expand_tokens(&tokens, shell);
	join_adjacent_tokens(&tokens);
	return (tokens);
}
