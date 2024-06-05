/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/05 18:55:57 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include "readline/history.h"
# include "readline/readline.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

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
	RPAREN
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char **args;       // Argumentos del comando
	char *input_file;  // Archivo de input para redirección
	char *output_file; // Archivo de output para redirección
	int append_output; // Flag de append
	int heredoc;       // Flag de heredoc
	int and;           // Flag de and
	int or ;           // Flag de or
	int parentheses;   // Flag de paréntesis
	int right_pipe;    // Flag de pipe a la derecha
	struct s_command	*next;
}						t_command;

typedef struct s_shell
{
	char				**env;
	t_command			*commands;
	char				*line;
	int					last_exit_status;
	int					parentheses;
}						t_shell;

t_shell					*init_shell(char **env);
void					free_str(char *str);
void					free_str_str(char **str);
void					free_shell(t_shell *shell);

t_token					*tokenize(char *line, t_shell *shell);
t_token					*create_basic_token(char type, char *value, int *i);
void					free_tokens(t_token *tokens);
void					add_token(t_token **tokens, t_token *new_token);
t_token					*new_token(t_token_type type, char *value);
t_token					*handle_space(const char *line, int *i);
t_token					*handle_word(char *line, int *i);
int						handle_end_quotes(int *i, char *line, t_shell *shell,
							char c);
t_token					*handle_left_parentheses(char *line, int *i,
							t_shell *shell);
t_token					*handle_right_parentheses(t_shell *shell, int *i);

char					*ft_strndup(const char *s, size_t n);
int						ft_is_space(char line);
void					*ft_realloc(void *ptr, size_t original_size,
							size_t new_size);
void					handle_error(char *message, t_shell *shell);
int						ft_strcmp(const char *s1, const char *s2);

#endif