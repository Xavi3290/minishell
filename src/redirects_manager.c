/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:50:29 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/14 10:56:15 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_output_file(char *file_name, int append, t_shell *shell)
{
	int	fd;

	if (append)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error(NULL, shell, 0);
	close(fd);
}