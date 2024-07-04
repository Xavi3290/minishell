/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/04 16:54:20 by xroca-pe         ###   ########.fr       */
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
void free_commands(t_command *cmd)
{
    t_command *current;
    t_command *next;
    int i;
    current = cmd;
    while (current)
    {
        next = current->next;
        if (current->args)
        {
            for (i = 0; current->args[i]; i++)
                free(current->args[i]);
            free(current->args);
        }
        if (current->input_files)
        {
            for (i = 0; current->input_files[i]; i++)
                free(current->input_files[i]);
            free(current->input_files);
        }
        if (current->output_files)
        {
            for (i = 0; current->output_files[i]; i++)
                free(current->output_files[i]);
            free(current->output_files);
        }
        free(current);
        current = next;
    }
}

void process_tokens_and_export(t_shell *shell, t_token *tokens)
{
    int i = 0;
    t_token *temp2 = tokens;
    while (temp2)
    {
        shell->commands->num_args = i + 1;
        shell->commands->args[i] = temp2->value;
        i++;
        temp2 = temp2->next;
    }
    shell->commands->args[i] = NULL;
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
            //tokens = tokenize(shell->line, shell);
            tokens = tokenize_and_expand(shell->line, shell);
            if (!tokens)
            {
                free(shell->line);
                shell->line = NULL;
                //handle_error("Tokenization failed", shell);
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
            if (shell->commands)
            {
                print_command(shell->commands);
                free_commands(shell->commands);
            }
            shell->commands = malloc(sizeof(t_command));
            shell->commands->args = malloc(sizeof(char *) * 1000);
            t_token *temp;
            temp = tokens;
            while (temp)
            {
				if (!ft_strcmp(temp->value, "export"))
				{
    				process_tokens_and_export(shell, tokens);
    				ft_export(shell->commands, shell);
				}
				else if (!ft_strcmp(temp->value, "unset"))
				{
					process_tokens_and_export(shell, tokens);
					ft_unset(shell, shell->commands);
				}
				else if (!ft_strcmp(temp->value, "exit"))
				{
					process_tokens_and_export(shell, tokens);
					ft_exit(shell);
				}
				else if (!ft_strcmp(temp->value, "echo"))
				{
					process_tokens_and_export(shell, tokens);
					ft_echo(&shell->commands);
				}
                else if (!ft_strcmp(temp->value, "env"))
                    ft_env(shell);
                else if (!ft_strcmp(temp->value, "pwd"))
                    ft_pwd();
                /*else
					printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);*/
                temp = temp->next;
            }
            //parse_tokens(tokens, shell);
            //print_commands(shell->commands);
            /*t_token   *temp;
            temp = tokens;
            while (temp)
            {
                printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
                temp = temp->next;
            }*/
            // Parse the tokens into commands
            // Execute the commandss
            // Free the commands
            free(shell->commands->args);
            free(shell->commands);
            //shell->parentheses = 0;
            free_tokens(tokens);
            free(shell->line);
            shell->line = NULL;
            //shell = init_shell(env);
        }
    }
    free_shell(shell);
    return (0);
}
