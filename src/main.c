/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/03 16:21:23 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_commands(t_command *commands)
{
    t_command *current_command;
    int i;
    current_command = commands;
    while (current_command)
    {
        printf("Command:\n");
        printf("  Arguments:\n");
        for (i = 0; i < current_command->num_args; i++)
        {
            printf("    arg[%d]: %s\n", i, current_command->args[i]);
        }
        printf("  Input Files:\n");
        for (i = 0; i < current_command->num_inputs; i++)
        {
            printf("    input[%d]: %s\n", i, current_command->input_files[i]);
        }
        printf("  Output Files:\n");
        for (i = 0; i < current_command->num_outputs; i++)
        {
            printf("    output[%d]: %s\n", i, current_command->output_files[i]);
        }
        printf("  Append Output: %d\n", current_command->append_output);
        printf("  Heredoc: %d\n", current_command->heredoc);
        printf("  AND: %d\n", current_command->and);
        printf("  OR: %d\n", current_command->or);
        printf("  Parentheses: %d\n", current_command->parentheses);
        printf("\n");
        current_command = current_command->next;
    }
}
void free_command(t_command *command)
{
    int i;
    if (command)
    {
        if (command->args)
        {
            for (i = 0; i < command->num_args; i++)
            {
                free(command->args[i]);
            }
            free(command->args);
        }
        if (command->input_files)
        {
            for (i = 0; i < command->num_inputs; i++)
            {
                free(command->input_files[i]);
            }
            free(command->input_files);
        }
        if (command->output_files)
        {
            for (i = 0; i < command->num_outputs; i++)
            {
                free(command->output_files[i]);
            }
            free(command->output_files);
        }
        free(command);
    }
}
void free_commands(t_command *commands)
{
    t_command *current_command;
    t_command *next_command;
    current_command = commands;
    while (current_command)
    {
        next_command = current_command->next;
        free_command(current_command);
        current_command = next_command;
    }
}
int main(int argc, char **argv, char **env)
{
    t_shell *shell;
    t_token *tokens;
    t_command *commands;
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
        shell->line = readline("mini:shell:: ");
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
            commands = parse_commands(tokens);
            if (commands)
            {
                print_commands(commands);
                free_commands(commands);
            }
            shell->commands = malloc(sizeof(t_command));
            shell->commands->args = malloc(sizeof(char *) * 1000);
            t_token *temp;
            temp = tokens;
            while (temp)
            {
                /*if (!ft_strcmp(temp->value, "export"))
                {
                    shell->commands->num_args = 2;
                    shell->commands->args[0] = "export";
                    temp = temp->next;
                    temp = temp->next;
                    //printf("%s\n",temp->value);
                    shell->commands->args[1] = temp->value;
                    //temp = temp->next;
                    //temp = temp->next;
                    //printf("%s\n",temp->value);
                    //shell->commands->args[2] = temp->value;
                    shell->commands->args[2] = NULL;
                    ft_export(shell->commands, shell);
                    //ft_exit(shell);
                }*/
                if (!ft_strcmp(temp->value, "env"))
                    ft_env(shell);
                else if (!ft_strcmp(temp->value, "pwd"))
                    ft_pwd();
                //else
                //      printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
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
            shell->parentheses = 0;
            free_tokens(tokens);
            free(shell->line);
            shell->line = NULL;
            //shell = init_shell(env);
        }
    }
    free_shell(shell);
    return (0);
}
