/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:23:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/20 16:35:49 by xroca-pe         ###   ########.fr       */
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
