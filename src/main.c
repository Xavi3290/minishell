/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/23 18:15:15 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    main(int argc, char **argv, char **env)
{
    t_shell *shell;
    
    (void)argc;
    (void)argv;
    shell = init_shell(env);
    while (1)
    {
        shell->line = readline("minishell: ");
        // Tokenize the input line
        // Parse the tokens into commands
        // Execute the commands
        // Free the commands    
        free(shell->line);
        shell->line = NULL;
    }   
    
    return (0);
}