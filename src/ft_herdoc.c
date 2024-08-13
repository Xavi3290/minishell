/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:07:07 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/13 13:07:31 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sig_hered);
	signal(SIGQUIT, SIG_IGN);
}

void	process_heredoc_input(t_command *cmd, int i, int fd, t_shell *shell)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if ((ft_strlen(line) - 1) == ft_strlen(cmd->delimiter[i]) && \
			ft_strncmp(line, cmd->delimiter[i], \
			ft_strlen(cmd->delimiter[i])) == 0)
		{
			free(line);
			break ;
		}
		if (*(cmd->type[i]) == WORD)
		{
			expanded = expand_variable(line, shell);
			ft_putstr_fd(expanded, fd);
			free(expanded);
		}
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
}

void	handle_herdoc(t_command *cmd, int i, t_shell *shell)
{
	setup_heredoc_signals();
	while (cmd->input_files[i])
	{
		cmd->fd = open(cmd->input_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->fd == -1)
		{
			handle_error("Failed to open heredoc file", shell);
			return ;
		}
		process_heredoc_input(cmd, i, cmd->fd, shell);
		close(cmd->fd);
		i++;
	}
}