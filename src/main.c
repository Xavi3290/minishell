/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/29 19:45:29 by xroca-pe         ###   ########.fr       */
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
		if (shell->line)
		{
			tokens = tokenize(shell->line, shell);
			if (!tokens)
			{
				free(shell->line);
				handle_error("Tokenization failed", shell);
				continue;
			}
			add_history(shell->line);
			// Parse the tokens into commands
			// Execute the commands
			// Free the commands		
			free_tokens(tokens);  
			ree(shell->line);
			shell->line = NULL;
		}		
	}
	free_shell(shell);
	return (0);
}
