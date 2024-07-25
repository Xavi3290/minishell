/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:37:33 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/25 14:50:46 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

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
			free_str_str(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	num_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = copy_env(env);
	if (!shell->env)
		return (NULL);
	shell->env_num = num_env(env);
	shell->commands = NULL;
	shell->line = NULL;
	shell->last_exit_status = 0;
	shell->parentheses = 0;
	return (shell);
}
