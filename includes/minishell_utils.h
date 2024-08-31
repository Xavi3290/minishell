/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:18:30 by cgaratej          #+#    #+#             */
/*   Updated: 2024/08/31 12:46:24 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

extern int	g_error;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	SPACES,
	AND,
	OR,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
	LPAREN,
	RPAREN,
	WILDC,
	DELIMITER
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_syntax
{
	int	last_was_operator;
	int	last_was_pipe;
	int	last_was_redirect;
	int	last_was_logical;
	int	paren_count;
	int	in_parentheses;
	int	paren_opened;
	int	last_was_word;
	int	num_heredocs;
}	t_syntax;

typedef struct s_command
{
	char				**args;
	int					num_args;
	char				**input_files;
	char				**output_files;
	char				**delimiter;
	t_token_type		**type;
	int					append_output;
	int					heredoc;
	int					and;
	int					or;
	int					parentheses;
	int					fd;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char		**env;
	int			env_num;
	t_command	*commands;
	char		*line;
	int			last_exit_status;
	int			parentheses;
	int			heredoc;
	int			flag_redirects;
	int			wildc;
}	t_shell;

#endif