/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:46 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/20 22:39:00 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int			check_is_num(char *str, t_shell *shell);
static long long	special_atoi(const char *str, int *atoi_error);
static void			free_exit(t_shell *shell, int n);

int	ft_exit(t_shell *shell, t_command *cmd)
{
	long long	n;
	int			atoi_error;
	int			i;

	atoi_error = 0;
	if (cmd->num_args == 1 || !cmd->args[1])
		free_exit(shell, 0);
	else if (cmd->args[2] && check_is_num(cmd->args[1], shell) \
			&& !shell->commands->next)
		return (put_error("exit\nminishell", "exit", "too many arguments"), 1);
	else if (cmd->args[2] && check_is_num(cmd->args[1], shell))
		return (put_error("minishell", "exit", "too many arguments"), 1);
	i = 0;
	while (cmd->args[++i])
		check_is_num(cmd->args[i], shell);
	n = special_atoi(cmd->args[1], &atoi_error);
	if (atoi_error == -1)
	{
		put_error("exit\nbash: exit", cmd->args[1], \
					"numeric argument required");
		free_commands(shell->commands);
		free(shell->line);
		exit(2);
	}
	return (free_exit(shell, n), 0);
}

static int	check_is_num(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			put_error("exit\nminishell: exit", \
					str, "numeric argument required");
			free_commands(shell->commands);
			free(shell->line);
			exit(2);
		}
		i++;
	}
	return (1);
}

static int	ft_atoi_error(int *atio)
{
	*atio = -1;
	return (-1);
}

static long long	special_atoi(const char *str, int *atoi_error)
{
	int			i;
	int			flag;
	long long	nbr;

	nbr = 0;
	i = 0;
	flag = 1;
	if (ft_strlen(str) > 19 \
		&& ft_strncmp("9223372036854775807", str, 20) < 0)
		ft_atoi_error(atoi_error);
	if (ft_strlen(str) == 20 && (ft_strncmp \
		("-9223372036854775807", str, 21) < 0 && ft_strlen(str) > 20))
		ft_atoi_error(atoi_error);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * flag);
}

static void	free_exit(t_shell *shell, int n)
{
	if (!shell->commands->next)
		printf("exit\n");
	free_commands(shell->commands);
	free(shell->line);
	if (!n)
		exit(shell->last_exit_status);
	else
		exit ((unsigned char)n);
}
