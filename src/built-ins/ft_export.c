/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:54:22 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/18 17:11:16 by cgaratej         ###   ########.fr       */
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
	while (cmd->args[++i] && i <= cmd->num_args)
	{
		tmp = remove_qutes(cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
	}
	tmp_arry = malloc(sizeof(char) * cmd->num_args + 1);
	if (!tmp_arry)
		return (0);
	i = 0;
	
}*/

/*int ft_export(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*arg;
	char	*equal_sign;
	char	*name;
	char	*value;
	
	i = 1;	
	if (cmd->num_args < 2)
		return (-1);
	while (i < cmd->num_args)
	{
		arg = cmd->args[i];
		equal_sign = strchr(arg, '=');
		if (equal_sign == NULL)
			return (-1);
		*equal_sign = '\0'; // Dividir el argumento en el nombre de la variable y el valor
		name = arg;
		value = equal_sign + 1;
		shell->env = realloc(shell->env, (shell->env_num + 2) * sizeof(char *));  // Expandir el array env
		if (shell->env == NULL)
			return (-1); // La función realloc devolvió un error
		shell->env[shell->env_num] = ft_strdup(name);
		shell->env[shell->env_num] = ft_strjoin(shell->env[shell->env_num], "=");
		shell->env[shell->env_num] = ft_strjoin(shell->env[shell->env_num], value); 
		printf("Exported %s\n", shell->env[shell->env_num]);
		shell->env_num++;
		shell->env[shell->env_num] = NULL;
		if (setenv(name, value, 1) != 0)
        	return (-1);
		i++;
	}
	return (0);
}*/
