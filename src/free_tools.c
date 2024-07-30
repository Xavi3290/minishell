/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:59:35 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/30 17:06:06 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void free_type(t_token_type **type)
{
    int i = 0;

    if (type)
    {
        while (type[i])
        {
            free(type[i]);
            i++;
        }
        free(type);
    }
}

void	free_commands(t_command *cmd)
{
	t_command	*current;
	t_command	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_string_array(current->args);
		free_string_array(current->input_files);
		free_string_array(current->output_files);
        free_string_array(current->delimiter);
        free_type(current->type);
		free(current);
		current = next;
	}
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
