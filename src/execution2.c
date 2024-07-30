/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/30 15:14:10 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void replace_heredoc_delimiter(t_command *cmd, int delimiter_index, int i)
{
    int k = 0;

    while (cmd->args[k])
    {
        if (ft_strncmp(cmd->args[k], cmd->args[delimiter_index], ft_strlen(cmd->args[delimiter_index])) == 0)
        {
            free(cmd->args[k]);
            cmd->args[k] = strdup(cmd->input_files[i]);
            return;
        }
        k++;
    }
    free(cmd->args[delimiter_index]);
    cmd->args[delimiter_index] = NULL;
}

void	handel_herdoc(t_command *cmd, int i)
{
	int		fd;
	char	*line;
	int		j;

	j = 1;
	while (cmd->input_files[i])
	{
		fd = open(cmd->input_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			if (ft_strncmp(line, cmd->args[j], ft_strlen(cmd->args[j])) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			free(line);
		}
		close(fd);
		replace_heredoc_delimiter(cmd, 1, i);
        free(cmd->args[j]);
        cmd->args[j++] = NULL;
		i++;
	}
	print_command(cmd);
}

void	execute_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		/*if (cmd->heredoc)
			handel_herdoc(cmd, 0);*/
		exec_cmd(shell->env, cmd);
	}
	else if (pid < 0)
		handle_error("minishell: fork", shell);
	else
		waitpid(pid, &(shell->last_exit_status), 0);
}

void	wait_for_children(pid_t *pids, int num_childrens, t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_childrens)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
}

int	count_comands(t_command *cmd)
{
	int			num_commands;
	t_command	*current;
	int			herdoc_count;

	num_commands = 0;
	current = cmd;
	herdoc_count = 0;
	while (current)
	{
		num_commands++;
		//Xavi poner numero de herdocs
		/*if (herdoc_count > MAX_HEREDOCS)
        {
            execution_error("minishell: tmaximum here-document count exceeded\n", 0, 2, NULL);
            return (0);
        }*/
		current = current->next;
	}
	return (num_commands);
}