/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:59:35 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/22 17:25:20 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_commands(t_command *cmd)
{
    t_command *current;
    t_command *next;

    int i;
    current = cmd;
    while (current)
    {
        next = current->next;
        if (current->args)
        {
            for (i = 0; current->args[i]; i++)
                free(current->args[i]);
            free(current->args);
        }
        if (current->input_files)
        {
            for (i = 0; current->input_files[i]; i++)
                free(current->input_files[i]);
            free(current->input_files);
        }
        if (current->output_files)
        {
            for (i = 0; current->output_files[i]; i++)
                free(current->output_files[i]);
            free(current->output_files);
        }
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
	free(tokens);
}
