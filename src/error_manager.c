/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:30:37 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/10 15:38:57 by cgaratej         ###   ########.fr       */
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
