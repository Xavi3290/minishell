/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/30 15:36:06 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static t_command *new_command(void)
{
    t_command *cmd;
    
    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = 0;
    cmd->heredoc = 0;
    cmd->and = 0;
    cmd->or = 0;
    cmd->next = NULL;
    return (cmd);    
}

static void add_command(t_command **cmd, t_command *new)
{
    t_command *last;

    if (!*cmd)
    {
        *cmd = new;
        return ;
    }
    last = *cmd;
    while (last->next)
        last = last->next;
    last->next = new;
}

static void free_command(t_command *commands)
{
    t_command *cmd;
    t_command *next;
    
    cmd = commands;
    while (cmd)
    {
        next = cmd->next;
        free(cmd->args);
        free(cmd->input_file);
        free(cmd->output_file);
        free(cmd);
        cmd = next;
    }
}*/

