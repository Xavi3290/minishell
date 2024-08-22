/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:38:08 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 16:50:56 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_token_values(t_token *current, t_token *next)
{
	char	*joined_value;

	joined_value = ft_strjoin(current->value, next->value);
	free(current->value);
	current->value = joined_value;
	current->next = next->next;
	free(next->value);
	free(next);
	if (current->type == DELIMITER)
		current->type = DOUBLE_QUOTES;
}
