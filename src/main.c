/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/18 14:43:32 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
        printf("  Append Output: %d\n", cmd->append_output);
        printf("  Heredoc: %d\n", cmd->heredoc);
        printf("  AND: %d\n", cmd->and);
        printf("  OR: %d\n", cmd->or);
        printf("  Parentheses: %d\n", cmd->parentheses);
        printf("\n");
        cmd = cmd->next;
    }
}

int main(int argc, char **argv, char **env)
{
	t_shell *shell;
    t_token *tokens;

    (void)argc;
    (void)argv;
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
			free_tokens(tokens);
            execute_commands(shell);
            /*if (shell->commands)
            {
                print_command(shell->commands);
            }*/
			/*if (!ft_strcmp(shell->commands->args[0], "export"))
    			ft_export(shell->commands, shell);
			else if (!ft_strcmp(shell->commands->args[0], "unset"))
				ft_unset(shell, shell->commands);
			else if (!ft_strcmp(shell->commands->args[0], "exit"))
				ft_exit(shell);
			else if (!ft_strcmp(shell->commands->args[0], "echo"))
				ft_echo(&shell->commands);
            else if (!ft_strcmp(shell->commands->args[0], "env"))
                ft_env(shell);
            else if (!ft_strcmp(shell->commands->args[0], "pwd"))
                ft_pwd();
			else if (!ft_strcmp(shell->commands->args[0], "cd"))
				ft_cd(shell);*/
            //parse_tokens(tokens, shell);
            //print_commands(shell->commands);
            /*t_token   *temp;
            temp = tokens;
            while (temp)
            {
                printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
                temp = temp->next;
            }*/
			free_commands(shell->commands);
            shell->parentheses = 0;
            //free_tokens(tokens);
            free(shell->line);
            shell->line = NULL;
        }
    }
    free_shell(shell);
    return (0);
}
