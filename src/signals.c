/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:01:00 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/08 17:52:28 by xroca-pe         ###   ########.fr       */
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
		rl_on_new_line();
		rl_redisplay();
		ft_putendl_fd("", 1);
		error_exit = 1;
		exit(1);
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

void	handle_signals(int status, t_shell *shell)
{
	if (WIFEXITED(status))
	{
		error_exit = WEXITSTATUS(status);
		shell->last_exit_status = error_exit;
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		error_exit = WTERMSIG(status) + 128;
		shell->last_exit_status = error_exit;
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

void	handle_eof()
{
	write(1, "exit\n", 5);
	exit(0);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);  // ctrl-C
	signal(SIGQUIT, handle_sigquit); // ctrl-\ ;
}*/