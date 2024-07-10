/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:22:53 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/10 13:36:46 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void redirect_input(char *file, t_shell *shell)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        handle_error("minishell: open", shell);
    if (dup2(fd, STDIN_FILENO) < 0)
        handle_error("minishell: dup2", shell);
    close(fd);
}

void redirect_output(char *file, int append, t_shell *shell)
{
    int fd;
    if (append)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        handle_error("minishell: open", shell);
    if (dup2(fd, STDOUT_FILENO) < 0)
        handle_error("minishell: dup2", shell);
    close(fd);
}

void handle_heredoc(t_command *cmd, t_shell *shell)
{
    if (cmd->heredoc && cmd->input_files)
    {
        int fd = open(cmd->input_files[0], O_RDONLY);
        if (fd < 0)
            handle_error("minishell: open", shell);
        if (dup2(fd, STDIN_FILENO) < 0)
            handle_error("minishell: dup2", shell);
        close(fd);
    }
}

void execute_simple_command(t_command *cmd, t_shell *shell)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (cmd->input_files)
            redirect_input(cmd->input_files[0], shell);
        if (cmd->output_files)
            redirect_output(cmd->output_files[0], cmd->append_output, shell);
        handle_heredoc(cmd, shell);
        if (execvp(cmd->args[0], cmd->args) < 0)
            handle_error("minishell: execvp", shell);
    }
    else if (pid < 0)
    {
        handle_error("minishell: fork", shell);
    }
    else
    {
        waitpid(pid, &(shell->last_exit_status), 0);
    }
}

void close_pipe(int pipe_fd[2])
{
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

void create_child_process(t_command *cmd, int in_fd, int pipe_fd[2], t_shell *shell)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        dup2(in_fd, STDIN_FILENO);
        if (cmd->next)
            dup2(pipe_fd[1], STDOUT_FILENO);
        close_pipe(pipe_fd);
        if (cmd->input_files)
            redirect_input(cmd->input_files[0], shell);
        if (cmd->output_files)
            redirect_output(cmd->output_files[0], cmd->append_output, shell);
        handle_heredoc(cmd, shell);
        if (execvp(cmd->args[0], cmd->args) < 0)
            handle_error("minishell: execvp", shell);
    }
    else if (pid < 0)
    {
        handle_error("minishell: fork", shell);
    }
}

void process_pipeline(t_command *cmd, t_shell *shell)
{
    int pipe_fd[2];
    int in_fd = STDIN_FILENO;

    while (cmd)
    {
        pipe(pipe_fd);
        create_child_process(cmd, in_fd, pipe_fd, shell);
        close(pipe_fd[1]);
        in_fd = pipe_fd[0];
        cmd = cmd->next;
    }
}

void execute_pipeline(t_command *cmd, t_shell *shell)
{
    process_pipeline(cmd, shell);
    while (cmd)
    {
        wait(NULL);
        cmd = cmd->next;
    }
}

void execute_parentheses(t_command *cmd, t_shell *shell)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        shell->commands = cmd;
        execute_commands(shell);
        exit(shell->last_exit_status);
    }
    else if (pid < 0)
    {
        handle_error("minishell: fork", shell);
    }
    else
    {
        waitpid(pid, &(shell->last_exit_status), 0);
    }
}

void execute_commands(t_shell *shell)
{
    t_command *cmd = shell->commands;

    while (cmd)
    {
        if (cmd->args && cmd->args[0])
        {
            if (cmd->next && cmd->next->args && cmd->next->args[0] && cmd->next->args[0][0] == '|')
                execute_pipeline(cmd, shell);
            else
                execute_simple_command(cmd, shell);
        }
        else if (cmd->parentheses)
            execute_parentheses(cmd, shell);
        
        if (cmd->and && shell->last_exit_status == 0)
            cmd = cmd->next;
        else if (cmd->or && shell->last_exit_status != 0)
            cmd = cmd->next;
        else
            cmd = cmd->next;
    }
}
