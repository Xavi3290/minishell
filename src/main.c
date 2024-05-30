/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/30 15:57:57 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	t_token	*tokens;
	t_token *temp;

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
		shell->line = readline("minishell: ");
		if (shell->line[0])
		{
			tokens = tokenize(shell->line, shell);
			if (!tokens)
			{
				free(shell->line);
				handle_error("Tokenization failed", shell);
				continue;
			}
			add_history(shell->line);
			temp = tokens;
			while (temp)
			{
				printf("Token: Type=%d, Value=%s\n", temp->type, temp->value);
				temp = temp->next;
			}
			// Parse the tokens into commands
			// Execute the commands
			// Free the commands		
			free_tokens(tokens);  
			free(shell->line);
			shell->line = NULL;
		}		
	}
	free_shell(shell);
	return (0);
}

