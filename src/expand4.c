/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:23:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/10 15:44:38 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_dollar_signs(char *str, int i)
{
	int		dollar_count;
	char	*dollar_str;
	char	*dup;

	dollar_count = 0;
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
		return (dup);
	}
	return (ft_strdup(""));
}

void	join_adjacent_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	char	*joined_value;

	current = *tokens;
	while (current && current->next)
	{
		next = current->next;
		if (next->type == WORD || next->type == DOUBLE_QUOTES \
			|| next->type == SINGLE_QUOTES)
		{
			if (current->type == WORD || current->type == DOUBLE_QUOTES \
			|| current->type == SINGLE_QUOTES)
			{
				joined_value = ft_strjoin(current->value, next->value);
				free(current->value);
				current->value = joined_value;
				current->next = next->next;
				free(next->value);
				free(next);
				continue ;
			}
		}
		current = current->next;
	}
}
