/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:13:04 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/26 12:37:35 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error;

static t_shell	*initialize_shell(int argc, char **env)
{
	t_shell	*shell;

	if (argc > 1)
	{
		printf("minishell: too many arguments\n");
		exit(1);
	}
	shell = init_shell(env);
	if (!shell)
	{
		perror("minishell: Initialization failed\n");
		exit(errno);
	}
	return (shell);
}

static void	parse_execute_frees(t_token *tokens, t_shell *shell)
{
	t_command	*current;

	parse_tokens(&tokens, shell);
	current = shell->commands;
	while (current)
	{
		if (current->num_args > 0)
		{
			if (shell->flag_redirects)
				execute_commands(shell);
			break ;
		}
		current = current->next;
	}
	shell->flag_redirects = 1;
	shell->parentheses = 0;
	free_tokens(tokens);
	free_herdocs(shell->commands);
	free_commands(shell->commands);
	free(shell->line);
	shell->line = NULL;
}

static void	signals_and_readline(t_shell *shell)
{
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
}

static void	process_command_line(t_shell *shell)
{
	t_token	*tokens;

	while (42)
	{
		signals_and_readline(shell);
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
