/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/19 16:23:31 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void print_commands(t_command *commands)
{
    t_command *cmd;
    int i;

    cmd = commands;
    while (cmd)
    {
        printf("Command:\n");
        if (cmd->args)
        {
            printf("  Arguments:\n");
            for (i = 0; cmd->args[i]; i++)
                printf("    %s\n", cmd->args[i]);
        }
        if (cmd->input_files)
        {
            printf("  Input Files:\n");
            for (i = 0; cmd->input_files[i]; i++)
                printf("    %s\n", cmd->input_files[i]);
        }
        if (cmd->output_files)
        {
            printf("  Output Files:\n");
            for (i = 0; cmd->output_files[i]; i++)
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
}*/

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	t_token	*tokens;

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
			//tokens = tokenize(shell->line, shell);
			tokens = tokenize_and_expand(shell->line, shell);
			if (!tokens)
			{
				free(shell->line);
				handle_error("Tokenization failed", shell);
				continue ;
			}
			add_history(shell->line);
			t_token	*temp;
			temp = tokens;
			while (temp)
			{
				if (!ft_strcmp(temp->value, "cd"))
				{
					shell->commands = malloc(sizeof(t_command));
					shell->commands->args = malloc(sizeof(char *) * 1000);
					shell->commands->num_args = 1;
					shell->commands->args[0] = ft_strdup("src");
					if (ft_cd(&shell) == -1)
						printf("Error\n");
					free(shell->commands->args);
				}
				if (!ft_env(temp, shell))
				{
					if (!ft_strcmp(temp->value, "pwd"))
						ft_pwd();
					else
						printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
				}
				temp = temp->next;
			}
			//parse_tokens(tokens, shell);
			//print_commands(shell->commands);
			/*t_token	*temp;
			temp = tokens;
			while (temp)
			{
				printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
				temp = temp->next;
			}*/
			
			// Parse the tokens into commands
			// Execute the commands
			// Free the commands
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
