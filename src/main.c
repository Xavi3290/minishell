/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/20 22:59:06 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//int	g_error;

/*void print_command(t_command *cmd) 
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
}*/

int	check_only_space(char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\v' || s[i] == '\f'
			|| s[i] == '\r' || s[i] == ' ')
			j++;
	}
	if (j == i)
		return (-1);
	return (0);
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
	parse_tokens(&tokens, shell);
	if (shell->commands->num_args > 0)
		execute_commands(shell);
	//print_command(shell->commands);
	shell->parentheses = 0;
	shell->flag_redirects = 1;
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
		if (!shell->line)
			handle_eof();
        if (check_only_space(shell->line) == -1 || shell->line[0] == '\0')
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
