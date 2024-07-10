/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:23:12 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/10 15:40:36 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
void	expand_tokens(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	t_token	*new_tokens;
	char	**expansions;
	char	*expanded;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD && ft_strchr(current->value, '$'))
		{
			expanded = expand_variable(current->value, shell);
			if (expanded && expanded[0] != '\0')
			{
				new_tokens = tokenize(expanded, shell);
				insert_tokens(tokens, new_tokens, prev, current);
				if (prev)
					current = prev->next;
				else
					current = *tokens;
				free(expanded);
				continue ;
			}
		}
		else if (current->type == DOUBLE_QUOTES && ft_strchr(current->value,
					'$'))
		{
			expanded = expand_variable(current->value, shell);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		else if (current->type == WORD && ft_strchr(current->value, '*'))
		{
			expansions = expand_wildcards(current->value);
			if (expansions)
			{
				new_tokens = strings_to_tokens(expansions);
				insert_tokens(tokens, new_tokens, prev, current);
				if (prev)
					current = prev->next;
				else
					current = *tokens;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
}
*/
//5
void	expand_variable_token(t_token **tokens, t_shell *shell,
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
}
//4

void	expand_double_quotes_token(t_token *current, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(current->value, shell);
	if (expanded)
	{
		free(current->value);
		current->value = expanded;
	}
}
//3

void	expand_wildcard_token(t_token **tokens, t_shell *shell,
		t_token **current, t_token **prev)
{
	char	**expansions;
	t_token	*new_tokens;

	expansions = expand_wildcards((*current)->value, shell);
	if (expansions)
	{
		new_tokens = strings_to_tokens(expansions);
		insert_tokens(tokens, new_tokens, *prev, *current);
		if (*prev)
			*current = (*prev)->next;
		else
			*current = *tokens;
	}
}
//2

void	expand_tokens(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD && ft_strchr(current->value, '$'))
		{
			expand_variable_token(tokens, shell, &current, &prev);
		}
		else if (current->type == DOUBLE_QUOTES && ft_strchr(current->value, \
			'$'))
		{
			expand_double_quotes_token(current, shell);
		}
		else if (current->type == WORD && ft_strchr(current->value, '*'))
		{
			expand_wildcard_token(tokens, shell, &current, &prev);
		}
		prev = current;
		current = current->next;
	}
}

//1
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
