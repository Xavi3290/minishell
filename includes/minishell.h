/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/20 15:32:03 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "minishell_utils.h"
# include <errno.h>
# include <fcntl.h>
# include "readline/history.h"
# include "readline/readline.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <unistd.h>
# include <dirent.h>

t_shell	*init_shell(char **env);
void	free_str(char *str);
void	free_str_str(char **str);
void	free_shell(t_shell *shell);

t_token	*tokenize(char *line, t_shell *shell);
t_token	*create_basic_token(char type, char *value, int *i);
void	free_tokens(t_token *tokens);
void	add_token(t_token **tokens, t_token *new_token);
t_token	*new_token(t_token_type type, char *value);
t_token	*handle_space(const char *line, int *i);
t_token	*handle_word(char *line, int *i);
int		handle_end_quotes(int *i, char *line, t_shell *shell, char c);
t_token	*handle_left_parentheses(char *line, int *i, t_shell *shell);
t_token	*handle_right_parentheses(t_shell *shell, int *i);

char	*ft_strndup(const char *s, size_t n);
int		ft_is_space(char line);
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);
void	handle_error(char *message, t_shell *shell);
int		ft_strcmp(const char *s1, const char *s2);

int		ft_env(t_token *cmd, t_shell *shell);
int		ft_pwd(void);
char	*actual_path(void);
int		ft_cd(t_shell **shell);
void	put_error(char *bash, char *file, char *error);
//int 	ft_export(t_command *cmd, t_shell *shell);

t_token	*tokenize_and_expand(char *line, t_shell *shell);

//void 					parse_tokens(t_token *tokens, t_shell *shell);

#endif