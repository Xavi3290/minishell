/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:14:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/06/18 18:03:30 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_value(char *path_actual, t_shell *shell, int flag)
{
	int		i;
	char 	*tmp;

	i = -1;
	while (++i < shell->env_num)
	{
		if (!flag && shell->env[i] && !ft_strncmp(shell->env[i], "OLDPWD", 6))
		{
			tmp = ft_strjoin("OLDPWD=", path_actual);
			free(shell->env[i]);
			shell->env[i] = tmp;
		}
		else if (flag && shell->env[i] && !ft_strncmp(shell->env[i], "PWD", 3))
		{
			tmp = ft_strjoin("PWD=", path_actual);
			free(shell->env[i]);	
			shell->env[i] = tmp;
		}
	}
	free(path_actual);
}

int	ft_cd(t_shell **shell)
{
	int		i;
	char	*tmp;
	char 	*path_actual;

	i = 0;
	path_actual = actual_path();
	pwd_value(path_actual, (*shell), 0);
	if ((*shell)->commands->num_args == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	tmp = remove_qutes((*shell)->commands->args[0]);
	if (!ft_strncmp(tmp, "~", 1))
		chdir(getenv("OLDPWD"));
	else if (chdir(tmp) == -1)
		return(1); //error
	else
	{
		free(tmp);
		pwd_value(path_actual, (*shell), 1);
		return (0);
	}
	free(tmp);
	return (1);
}