/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:50:29 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/14 15:01:44 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_output_file(char *file_name, int append, t_shell *shell)
{
	int	fd;

	if (shell->flag_redirects)
	{
		if (append)
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			shell->flag_redirects = 0;
		close(fd);
	}
}

void	create_input_file(char *file_name, t_shell *shell)
{
	int	fd;

	if (shell->flag_redirects)
	{
		fd = open(file_name, O_RDONLY, 0644);
		if (fd == -1 || access(file_name, R_OK) == -1)
			shell->flag_redirects = 0;
		close(fd);
	}
}