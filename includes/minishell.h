/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/23 18:54:47 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	WORD,         // Un palabra general (comandos, argumentos)
	PIPE,         // El símbolo de pipe '|' para crear pipelines
	REDIRECT_IN,  // El símbolo de redirección de entrada '<'
	REDIRECT_OUT, // El símbolo de redirección de salida '>'
	APPEND,       // El símbolo de redirección de salida con append '>>'
	HEREDOC,      // El símbolo de heredoc '<<'
	//SINGLE_QUOTE, // Comilla simple '
	//DOUBLE_QUOTE,  // Comilla doble "
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char		**args;    // Argumentos del comando
	char		*input_file;  // Archivo de input para redirección
	char		*output_file; // Archivo de output para redirección
	int			append_output; // Modo de agregar output
	struct s_command	*next;
}						t_command;

typedef struct s_shell
{
	char				**env;
	t_command			*commands;
	char				*line;
}						t_shell;

t_shell	*init_shell(char **env);
void	free_str(char *str);
void	free_str_str(char **str);
void	free_shell(t_shell *shell);
char	*ft_strdup(const char *s1);

#endif
