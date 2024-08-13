/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:02:49 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/13 12:38:46 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "minishell_utils.h"
# include "readline/history.h"
# include "readline/readline.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <unistd.h>

t_shell		*init_shell(char **env);
void		free_str(char *str);
void		free_string_array(char **str);
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
void		handle_errors(char *message, t_shell *shell, int error);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen_d(char **str);

int			ft_env(t_shell *shell, t_command *cmd);
int			ft_pwd(t_shell *shell, t_command *cmd);
char		*actual_path(t_shell *shell);
int			ft_cd(t_shell *shell, t_command *cmd);
void		put_error(char *bash, char *file, char *error);
int			ft_exit(t_shell *shell, t_command *cmd);
int			ft_echo(t_command **command);
int			ft_export(t_command *cmd, t_shell *shell);
int			ft_unset(t_shell *shell, t_command *cmd);

/*expor utils*/
void		find_existing_var_indices(t_shell *shell, char *name,
				int *existing_var_index, int *existing_var);
int			check_env_var(t_shell *shell, char *name, char *arg);
int			add_env_var(t_shell *shell, char *arg);
char		*is_set_env(const char *arg);

t_token		*tokenize_and_expand(char *line, t_shell *shell);
void		remove_empty_token(t_token **tokens, t_token **current,
				t_token **prev);

char		*handle_dollar_signs(char *str, int i);
char		*expand_variable(char *str, t_shell *shell);
char		**expand_wildcards(const char *pattern, t_shell *shell);
t_token		*strings_to_tokens(char **strings);
void		insert_tokens(t_token **tokens, t_token *new_tokens, t_token *prev,
				t_token *current);
void		join_adjacent_tokens(t_token **tokens);

int			check_syntax(t_token *tokens, t_shell *shell);
int			handle_general_tokens_syn(t_token *token, t_syntax_state *state,
				t_shell *shell);
int			is_unmatched_rparen(t_syntax_state *state);

void		parse_tokens(t_token **tokens, t_shell *shell);
t_command	*create_command(void);
//void		add_heredoc_file(t_command *cmd, char *file);
void		add_heredoc_file(t_command *cmd, char *file, char *delimiter,
				t_token_type type);
void		add_argument(t_command *cmd, char *arg);
void		add_output_file(t_command *cmd, char *file, int append);
void		add_input_file(t_command *cmd, char *file);
void		handle_logical_token(t_token *current, t_command **cmd);
//void		handle_heredoc_token(t_command *cmd);
void		handle_heredoc_token(t_command *cmd, t_token **current);
void		handle_redirect_token(t_token **current, t_command *cmd,
				t_shell *shell, int type);

void		free_commands(t_command *cmd);
void		free_paths(char **path);

/*void parse_general_tokens_cmd(t_token **tokens, t_command *cmd, \
			t_shell *shell);
void	parse_parentheses(t_token **tokens, t_command *current_cmd, \
			t_shell *shell);
t_command	*create_command(void);
t_command	*parse_tokens_to_commands(t_token *tokens);
t_command	*parse_commands(t_token *tokens);
t_command	*parse_tokens_to_commands(t_token *tokens, t_shell *shell);
void	parse_tokens(t_token *tokens, t_shell *shell);*/

void		print_command(t_command *cmd);

void		exec_cmd(char **env, t_command *cmds, t_shell *shell);
int			cmd_type1(t_command *cmd, t_shell *shell);
int			cmd_type2(t_command *cmd, t_shell *shell);
void		execute_commands(t_shell *shell);
void		execute_simple_command(t_command *cmd, t_shell *shell);
void		handle_herdoc(t_command *cmd, int i, t_shell *shell);
int			count_comands(t_command *cmd);
void		execution_error(char *str, int per, int ex, char *cmd);
void		wait_for_children(pid_t *pids, int num_childrens, t_shell *shell);
void		wifstuff(t_shell *shell, int status);
void		create_pipeline(t_command *cmd, t_shell *shell, int num_commands, int i);
char		*get_path(char *cmd, char **env);
void		ft_redirectios(t_command *cmd);

void		handle_sig_normal(int sig);
void		handle_sig_hered(int sig);
void		handle_eof(void);
void		setup_signal_handlers(void);
//void		handle_signals(int status, t_shell *shell);
void		handle_signals(int status, t_shell *shell, int *first);

#endif