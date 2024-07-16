/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/16 16:34:39 by cgaratej         ###   ########.fr       */
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

t_shell		*init_shell(char **env);
void		free_str(char *str);
void		free_str_str(char **str);
void		free_shell(t_shell *shell);

t_token		*tokenize(char *line, t_shell *shell);
t_token		*create_basic_token(char type, char *value, int *i);
void		free_tokens(t_token *tokens);
void		add_token(t_token **tokens, t_token *new_token);
t_token		*new_token(t_token_type type, char *value);
t_token		*handle_space(const char *line, int *i);
t_token		*handle_word(char *line, int *i);
int			handle_end_quotes(int *i, char *line, t_shell *shell, char c);
t_token		*handle_left_parentheses(char *line, int *i, t_shell *shell);
t_token		*handle_right_parentheses(t_shell *shell, int *i);

char		*ft_strndup(const char *s, size_t n);
int			ft_is_space(char line);
void		*ft_realloc(void *ptr, size_t original_size, size_t new_size);
void		handle_error(char *message, t_shell *shell);
int			ft_strcmp(const char *s1, const char *s2);

int			ft_env(t_shell *shell);
int			ft_pwd(void);
char		*actual_path(void);
int			ft_cd(t_shell *shell);
void		put_error(char *bash, char *file, char *error);
void		ft_exit(t_shell *shell);
int			ft_echo(t_command **command);
int			ft_export(t_command *cmd, t_shell *shell);
int			ft_unset(t_shell *shell, t_command *cmd);

t_token		*tokenize_and_expand(char *line, t_shell *shell);

char		*handle_dollar_signs(char *str, int i);
char		*expand_variable(char *str, t_shell *shell);
char		**expand_wildcards(const char *pattern, t_shell *shell);
t_token		*strings_to_tokens(char **strings);
void		insert_tokens(t_token **tokens, t_token *new_tokens, t_token *prev, \
					t_token *current);
void		join_adjacent_tokens(t_token **tokens);

int			check_syntax(t_token *tokens, t_shell *shell);
int			handle_general_tokens_syn(t_token *token, t_syntax_state *state, \
			t_shell *shell);
int 		is_unmatched_rparen(t_syntax_state *state);

void		parse_tokens(t_token **tokens, t_shell *shell);
t_command	*create_command(void);
void		add_heredoc_file(t_command *cmd, char *file);
void		add_argument(t_command *cmd, char *arg);
void		add_output_file(t_command *cmd, char *file, int append);
void		add_input_file(t_command *cmd, char *file);
void		handle_logical_token(t_token *current, t_command **cmd);
void		handle_heredoc_token(t_command *cmd);
void		handle_redirect_token(t_token **current, t_command *cmd, \
			t_shell *shell, int type);

void 		free_commands(t_command *cmd);

void		exec_cmd(char *cmd, char **env);

/*void parse_general_tokens_cmd(t_token **tokens, t_command *cmd, \
			t_shell *shell);
void parse_parentheses(t_token **tokens, t_command *current_cmd, \
			t_shell *shell);
t_command *create_command(void);
t_command *parse_tokens_to_commands(t_token *tokens);
t_command *parse_commands(t_token *tokens);
t_command *parse_tokens_to_commands(t_token *tokens, t_shell *shell);
void	parse_tokens(t_token *tokens, t_shell *shell);*/

void		execute_commands(t_command *cmd, t_shell *shell);

#endif