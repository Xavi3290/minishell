/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/28 18:50:43 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
// # include <readline/history.h>
// # include <readline/readline.h>
//# include "../readline/history.h"
//# include "../readline/readline.h"
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
	OR
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
	int append_output; // Modo de agregar output
	struct s_command	*next;
}						t_command;

typedef struct s_shell
{
	char				**env;
	t_command			*commands;
	char				*line;
}						t_shell;

t_shell					*init_shell(char **env);
void					free_str(char *str);
void					free_str_str(char **str);
void					free_shell(t_shell *shell);
char					*ft_strndup(const char *s, size_t n);

t_token					*tokenize(char *line);
t_token					*create_basic_token(char type, char *value, int *i,
							int plus);
void					free_tokens(t_token *tokens);
void					add_token(t_token **tokens, t_token *new_token);
t_token					*new_token(t_token_type type, char *value);
int 					ft_is_space(char line);

#endif