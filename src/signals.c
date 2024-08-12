/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:01:00 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/12 17:42:15 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig_normal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		error_exit = 1;
	}
}

void	handle_sig_hered(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		// rl_on_new_line();
		// rl_redisplay();
		ft_putendl_fd("", 1);
		error_exit = 1;
		exit(130);
		//return (130);
	}
}

void	handle_eof(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signals(int status, t_shell *shell, int *first)
{
	if (WIFEXITED(status))
	{
		error_exit = WEXITSTATUS(status);
		shell->last_exit_status = error_exit;
	}
	else if (WIFSIGNALED(status) && (!first || *first))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			//error_exit = 131;
			shell->last_exit_status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			//error_exit = 130;
			shell->last_exit_status = 130;
		}
		//printf("%d\n", WTERMSIG(status));
		//error_exit = WTERMSIG(status) + 128;
		//shell->last_exit_status = error_exit;
		if (first)
			*first = 0;
	}
}

/*void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\nmini🐚: ", 9);
	error_exit = 1;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// No hacer nada en respuesta a ctrl-\ ;
}

void	handle_eof(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);  // ctrl-C
	signal(SIGQUIT, handle_sigquit); // ctrl-\ ;
}*/