/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:46 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 16:41:06 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int			check_is_num(char *str, t_shell *shell);
static long long	special_atoi(const char *str, int *atoi_error);
static void			free_exit(t_shell *shell, int n);

void	ft_exit(t_shell *shell)
{
	long long	n;
	int			atoi_error;
	int			i;

	atoi_error = 0;
	n = 0;
	if (shell->commands->num_args == 1 || !shell->commands->args[1])
		free_exit(shell, n);
	else if (shell->commands->args[2] && \
				check_is_num(shell->commands->args[1], shell))
		return (put_error("exit\nminishell", "exit", "too many arguments"));
	i = 0;
	while (shell->commands->args[++i])
		check_is_num(shell->commands->args[i], shell);
	n = special_atoi(shell->commands->args[1], &atoi_error);
	if (atoi_error == -1)
	{
		put_error("exit\nbash: exit", shell->commands->args[0], \
					"numeric argument required");
		free_commands(shell->commands);
		free(shell->line);
		exit(2);
	}
	free_exit(shell, n);
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
	if (ft_strlen(str) == 19 \
		&& ft_strncmp("9223372036854775807", str, 20) < 0)
		ft_atoi_error(atoi_error);
	if (ft_strlen(str) == 20 && (ft_strncmp \
		("-9223372036854775807", str, 21) < 0 || ft_strlen(str) > 20))
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
	printf("exit\n");
	free_commands(shell->commands);
	free(shell->line);
	if (!n)
		exit(shell->last_exit_status);
	else
		exit ((unsigned char)n);
}
