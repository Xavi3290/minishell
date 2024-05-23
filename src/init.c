/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:37:33 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/23 18:45:55 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **copy_env(char **env)
{
    char **new_env;
    int i;

    i = 0;
    while (env[i])
        i++;
    new_env = malloc((i + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    i = 0;
    while (env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
        {
            free(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

t_shell *init_shell(char **env)
{
    t_shell *shell;

    shell = malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    shell->env = copy_env(env);
    if (!shell->env)
        return (NULL);
    shell->commands = NULL;
    shell->line = NULL;
    return (shell);
}

void free_shell(t_shell *shell)
{
    char **env;
    t_command *command;
    t_command *next;

    env = shell->env;
    while (*env)
    {
        free(*env);
        env++;
    }
    free(shell->env);
    command = shell->commands;
    while (command)
    {
        next = command->next;
        free(command->args);
        free(command->input_file);
        free(command->output_file);
        free(command);
        command = next;
    }
    //free(shell->line);
    free(shell);
}
