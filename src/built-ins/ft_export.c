/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:54:22 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 17:36:55 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_and_print_env_var(char *env_var);
static void	pritn_declare(t_shell *shell, int i);
static int	validate_and_process_arg(char *arg, t_shell *shell);

int	ft_export(t_command *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (cmd->num_args < 2)
	{
		pritn_declare(shell, -1);
		return (0);
	}
	while (++i < cmd->num_args)
	{
		if (validate_and_process_arg(cmd->args[i], shell) != 0)
			return (1);
	}
	return (0);
}

static void	process_and_print_env_var(char *env_var)
{
	char	*copy_env_line;
	char	*equal_sign;

	copy_env_line = ft_strdup(env_var);
	if (copy_env_line != NULL)
	{
		equal_sign = ft_strchr(copy_env_line, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			if (copy_env_line[0] != '_')
				printf("declare -x %s=\"%s\"\n", copy_env_line, equal_sign + 1);
		}
		else
			printf("declare -x %s\n", copy_env_line);
		free(copy_env_line);
	}
}

static void	pritn_declare(t_shell *shell, int i)
{
	while (++i < shell->env_num)
	{
		if (shell->env[i] != NULL)
			process_and_print_env_var(shell->env[i]);
	}
}

static int	validate_and_process_arg(char *arg, t_shell *shell)
{
	char	*name;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
	{
		put_error("minishell: export", arg, "not a valid identifier");
		shell->last_exit_status = 1;
		return (0);
	}
	name = is_set_env(arg);
	if (!name)
		return (1);
	if (!check_env_var(shell, name, arg))
	{
		if (add_env_var(shell, arg) != 0)
		{
			free(name);
			return (1);
		}
	}
	free(name);
	return (0);
}
