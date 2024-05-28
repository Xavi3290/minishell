/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/28 19:48:58 by xroca-pe         ###   ########.fr       */
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
	while (1)
	{
		shell->line = readline("minishell: ");
		if (!shell->line)
		{
			perror("minishell: Readline failed\n");
			continue;
		}
		tokens = tokenize(shell->line);
		if (!tokens)
		{
			free(shell->line);
			perror("minishell: Tokenization failed\n");
			continue;
		}
		add_history(shell->line);
		// Parse the tokens into commands
		// Execute the commands
		// Free the commands
		
		free_tokens(tokens);  
		free(shell->line);
		shell->line = NULL;
	}
	free_shell(shell);
	return (0);
}
