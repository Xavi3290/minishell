/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:50:29 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/21 13:40:25 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_output_file(char *file_name, int append, t_shell *shell)
{
	int		fd;
	char	*error;

	if (shell->flag_redirects)
	{
		if (append)
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			shell->flag_redirects = 0;
			printf("2\n");
			error = ft_strjoin("minishell: ", file_name);
			perror(error);
			free(error);
			shell->last_exit_status = EXIT_FAILURE;
		}
		close(fd);
	}
}

void	create_input_file(char *file_name, t_shell *shell)
{
	int		fd;
	char	*error;

	if (shell->flag_redirects)
	{
		fd = open(file_name, O_RDONLY, 0644);
		if (fd == -1 || access(file_name, R_OK) == -1)
		{
			shell->flag_redirects = 0;
			printf("1\n");
			error = ft_strjoin("minishell: ", file_name);
			perror(error);
			free(error);
			shell->last_exit_status = EXIT_FAILURE;
		}
		close(fd);
	}
}
