/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:19:21 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/29 19:19:52 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_word(char *line, int *i)
{
	int		start;
	char	*value;
	t_token	*token;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '|' && line[*i] != '<'
		&& line[*i] != '>' && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	value = ft_strndup(&line[start], *i - start);
	if (!value)
		handle_error(NULL, NULL);
	token = new_token(WORD, value);
	(*i)--;
	return (token);
}