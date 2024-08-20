/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:37:33 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/20 13:49:07 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_shlvl(t_shell *shell)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;

	i = 0;
	while (i < shell->env_num)
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(shell->env[i] + 6);
			shlvl++;
			if (shlvl > 1000)
			{
				ft_putendl_fd("minishell: warning: shell level too high, resetting to 1", 2);
				shlvl = 1;
			}
			else if (shlvl < 0)
				shlvl = 0;
			new_shlvl = ft_itoa(shlvl);
			update_env_var(shell, "SHLVL=", new_shlvl);
			free(new_shlvl);
			return ;
		}
		i++;
	}
	//update_env_var(shell, "SHLVL=", "1");
}


char	**set_empty_env(void)
{
	char	**new_env;
	char	*cwd;

	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
		return (NULL);
	// Obtener el directorio actual y luego concatenarlo con "PWD="
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(new_env);
		return (NULL);
	}
	new_env[0] = ft_strjoin("PWD=", cwd);
	free(cwd);  // Liberar la memoria asignada por getcwd
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("_=/usr/bin/env");
	new_env[3] = NULL;

	return (new_env);
}



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
			free_string_array(new_env);
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
	if (env && env[0])
		shell->env = copy_env(env);
	else
		shell->env = set_empty_env();
	//shell->env = copy_env(env);
	if (!shell->env)
		return (NULL);
	shell->env_num = num_env(env);
	shell->commands = NULL;
	shell->line = NULL;
	shell->last_exit_status = 0;
	shell->parentheses = 0;
	shell->flag_redirects = 1;
	update_shlvl(shell);	
	return (shell);
}
