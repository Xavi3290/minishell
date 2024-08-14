/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:30:37 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/14 15:46:56 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(char *message, t_shell *shell)
{
	if (message)
		printf("minishell: %s\n", message);
	else
	{
		perror("minishell");
		exit(errno);
	}
	shell->last_exit_status = errno;
}

void	handle_errors(char *message, t_shell *shell, int error)
{
	if (message)
	{
		printf("minishell: %s\n", message);
		shell->last_exit_status = error;
	}
	else
	{
		perror("minishell");
		exit(errno);
	}
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

void	execution_error(char *str, int per, int ex, char *cmd)
{
	char	*error;

	error = NULL;
	if (per)
	{
		if (cmd)
			error = ft_strjoin(str, cmd);
		perror(error);
		free(error);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		exit(ex);
	}
}
