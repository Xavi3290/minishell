/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:30:37 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:45 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(char *message, t_shell *shell)
{
	if (message)
		printf("minishell: %s: %s\n", message, strerror(errno));
	else
	{
		perror("minishell");
		exit(errno);
	}
	shell->last_exit_status = errno;
}

void	put_error(char *bash, char *file, char *error)
{
	ft_putstr_fd(bash, 2);
	ft_putstr_fd(": ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putendl_fd(error, 2);
}

void	execution_error(char *cmd,char *message, t_shell *shell)
{
	printf("%s: %s\n", cmd, message);
	shell->last_exit_status = errno;
}

void	print_error(char *str, int per, int ex, char *cmd)
{
	if (per)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ex == 127)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("\n", 2);
			exit(ex);
		}
		ft_putstr_fd(str, 2);
		exit(ex);
	}
}
