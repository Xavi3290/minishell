/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 13:54:05 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

void print_command(t_command *cmd) 
{
    while (cmd)
    {
        printf("Command:\n");
        if (cmd->args)
        {
            printf("  Arguments:\n");
            for (int i = 0; cmd->args[i]; i++)
                printf("    %s\n", cmd->args[i]);
        }
        if (cmd->input_files)
        {
            printf("  Input Files:\n");
            for (int i = 0; cmd->input_files[i]; i++)
                printf("    %s\n", cmd->input_files[i]);
        }
        if (cmd->output_files)
        {
            printf("  Output Files:\n");
            for (int i = 0; cmd->output_files[i]; i++)
                printf("    %s\n", cmd->output_files[i]);
        }
        if (cmd->delimiter)
        {
            printf("  Delimeter:\n");
            for (int i = 0; cmd->delimiter[i]; i++)
                printf("    %s\n", cmd->delimiter[i]);
        }
        if (cmd->type)
        {
            printf("  Type: \n");
            for (int i = 0; cmd->type[i]; i++)
                printf("    %d\n", *(cmd->type[i]));
        }
        printf("  Append Output: %d\n", cmd->append_output);
        printf("  Heredoc: %d\n", cmd->heredoc);
        printf("  AND: %d\n", cmd->and);
        printf("  OR: %d\n", cmd->or);
        printf("  Parentheses: %d\n", cmd->parentheses);
        printf("\n");
        cmd = cmd->next;
    }
}

t_shell	*initialize_shell(int argc, char **env)
{
	t_shell	*shell;

	if (argc > 1)
	{
		printf("minishell: too many arguments\n");
		exit(1);
	}
	/*if (!env[0])
	{
		printf("minishell: no environment exists\n");
		exit(1);
	}*/
	shell = init_shell(env);
	if (!shell)
	{
		perror("minishell: Initialization failed\n");
		exit(errno);
	}
	return (shell);
}

void	parse_execute_frees(t_token *tokens, t_shell *shell)
{
	t_command	*current;

	parse_tokens(&tokens, shell);
	current = shell->commands;
	while (current)
	{
		if (current->num_args > 0)
		{
			//printf("a %d\n", shell->flag_redirects);
			if (shell->flag_redirects)
				execute_commands(shell);
			shell->flag_redirects = 1;
			break ;
		}
		current = current->next;
	}
	shell->flag_redirects = 1;
	//printf("b %d\n", shell->flag_redirects);
	//print_command(shell->commands);
	shell->parentheses = 0;
	free_tokens(tokens);
	if (shell->commands->heredoc)
		unlink(shell->commands->input_files[0]);
	free_commands(shell->commands);
	free(shell->line);
	shell->line = NULL;
}

void	process_command_line(t_shell *shell)
{
	t_token	*tokens;

	while (42)
	{
		//g_error = 0;
		signal(SIGINT, handle_sig_normal);
		signal(SIGQUIT, SIG_IGN);
		shell->line = readline("mini🐚: ");
        if (g_error)
        {
            shell->last_exit_status = 130;
            g_error = 0;
        }
		if (!shell->line)
			handle_eof(shell);
		if (ft_check_only_space(shell->line) == -1 || shell->line[0] == '\0')
			free(shell->line);
		else if (shell->line && shell->line[0])
		{
			add_history(shell->line);
			tokens = tokenize_and_expand(shell->line, shell);
			if (!tokens || !check_syntax(tokens, shell))
			{
				if (tokens)
					free_tokens(tokens);
				free(shell->line);
				shell->line = NULL;
				continue ;
			}
			parse_execute_frees(tokens, shell);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void)argv;
	shell = initialize_shell(argc, env);
	process_command_line(shell);
	free_shell(shell);
	return (0);
}

/*/int main(int argc, char **argv, char **env)
{
	t_shell *shell;
    t_token *tokens;

    (void)argv;
    if (argc > 1)
    {
        printf("minishell: too many arguments\n");
        return (1);
    }
    shell = init_shell(env);
    if (!shell)
    {
        perror("minishell: Initialization failed\n");
        return (errno);
    }
    while (42)
    {
        shell->line = readline("mini🐚: ");
        if (shell->line[0])
        {
            add_history(shell->line);
            tokens = tokenize_and_expand(shell->line, shell);
            if (!tokens)
            {
                free(shell->line);
                shell->line = NULL;
                continue ;
            }
            if (!check_syntax(tokens, shell))
            {
                free_tokens(tokens);
                free(shell->line);
                shell->line = NULL;
                continue;
            }
			parse_tokens(&tokens, shell);
            execute_commands(shell);
            print_command(shell->commands);
            t_token   *temp;
            temp = tokens;
            while (temp)
            {
                printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
                temp = temp->next;
            }
           shell->parentheses = 0;
            free_tokens(tokens);
			free_commands(shell->commands);
            free(shell->line);
            shell->line = NULL;
        }
    }
    free_shell(shell);
    return (0);
}*/
