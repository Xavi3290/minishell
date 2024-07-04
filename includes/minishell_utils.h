/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:18:30 by cgaratej          #+#    #+#             */
/*   Updated: 2024/07/04 15:13:55 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

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
	WILDC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_syntax_state
{
    int last_was_operator;
    int last_was_pipe;
    int last_was_redirect;
    int last_was_logical;
    int paren_count;
    int in_parentheses;
    int paren_opened;
    int last_was_word;
} t_syntax_state;

/*
typedef struct s_command
{
    char **args;            // Argumentos del comando
    int num_args;           // Número de argumentos del comando
    char **input_files;     // Archivos de input para redirección
    char **output_files;    // Archivos de output para redirección
    int append_output;      // Flag de append
    int heredoc;            // Flag de heredoc
    char **heredoc_files;   // Archivos de heredoc
    int and;                // Flag de and
    int or;                 // Flag de or
    int parentheses;        // Flag de paréntesis
    struct s_command *next;
} t_command;
*/

typedef struct s_command
{
    char        **args;          // Argumentos del comando
    int         num_args;        // Número de argumentos
    char        **input_files;   // Archivos de input
    char        **output_files;  // Archivos de output
    int         append_output;   // Flag de append
    int         heredoc;         // Flag de heredoc
    int         and;             // Flag de and
    int         or;              // Flag de or
    int         parentheses;     // Flag de paréntesis
    int         fd;              // File descriptor para heredoc
    struct s_command *next;      // Siguiente comando en la lista
} t_command;

typedef struct s_shell
{
	char				**env;
	int					env_num;
	t_command			*commands;
	char				*line;
	int					last_exit_status;
	int					parentheses;
}	t_shell;

#endif