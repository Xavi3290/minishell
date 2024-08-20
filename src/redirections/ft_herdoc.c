/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:07:07 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/20 16:05:19 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_line(char *line, t_command *cmd, int i, t_shell *shell)
{
	char	*expanded;

	if (*(cmd->type[i]) == WORD)
	{
		expanded = expand_variable(line, shell);
		ft_putstr_fd(expanded, cmd->fd);
		free(expanded);
	}
	else
		ft_putstr_fd(line, cmd->fd);
}

static void	process_heredoc_input(t_command *cmd, int i, t_shell *shell)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
		{
			//if (!g_error)
			handle_errors("warning: here-document delimited by end-of-file",
					shell, 0);
			//else
			//	free(line);
			exit(1);
		}
		if ((ft_strlen(line) - 1) == ft_strlen(cmd->delimiter[i]) && \
			ft_strncmp(line, cmd->delimiter[i], \
			ft_strlen(cmd->delimiter[i])) == 0)
		{
			free(line);
			break ;
		}
		process_line(line, cmd, i, shell);
		free(line);
	}
}

void	handle_herdoc(t_command *cmd, int i, t_shell *shell)
{
	signal(SIGINT, handle_sig_hered);
	while (cmd->input_files[i])
	{
		cmd->fd = open(cmd->input_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->fd == -1)
			handle_error("Failed to open heredoc file", shell);
		process_heredoc_input(cmd, i, shell);
		close(cmd->fd);
		i++;
	}
	exit(0);
}

void	process_heredocs(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		handle_error(NULL, NULL);
	if (pid == 0)
		handle_herdoc(cmd, 0, shell);
	else
		signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	wifstuff(shell, status);
}
