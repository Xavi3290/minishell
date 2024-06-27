/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:54:22 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/27 17:50:16 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int ft_export(t_command *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp_arry;

	i = -1;
	if (!cmd->args || !cmd->args[0])
		return (0);
	tmp_arry = malloc(sizeof(char) * cmd->num_args + 1);
	if (!tmp_arry)
		return (0);
	i = 0;
	
}*/

int ft_export(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*name;
    char	*value;
    char	*equal_sign;
    char	*arg_cpy;
    
	
	i = 1;	
	if (cmd->num_args < 2)
		return (-1);
	while (i < cmd->num_args)
	{
		arg_cpy = ft_strdup(cmd->args[i]);
		equal_sign = ft_strchr(arg_cpy, '=');
		if (equal_sign == NULL)
		{
			free(arg_cpy);
            return (-1);
		}
		*equal_sign = '\0';
        name = arg_cpy;
        value = equal_sign + 1;
		if (setenv(name, value, 1) != 0)
		{
			free(arg_cpy);
        	return (-1);
		}
		if (getenv(name) != NULL)
        {
            free(arg_cpy);
            i++;
            continue;
        }
		//shell->env = copy_env(env);
		shell->env = realloc(shell->env, (shell->env_num + 2) * sizeof(char *));  // Expandir el array env
		if (shell->env == NULL)
			return (-1); 
		shell->env[shell->env_num] = ft_strdup(cmd->args[i]);
		printf("Exported %s\n", shell->env[shell->env_num]);
		shell->env_num++;
		shell->env[shell->env_num] = NULL;
		i++;
	}
	return (0);
}
