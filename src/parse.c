/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/04 16:33:02 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static int generate_random_number(void) {
    static unsigned int seed = 12345;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (seed % 10000);
}

char *generate_filename(void) {
    char *str;
    char *num;
    num = ft_itoa(generate_random_number());
    str = ft_strjoin("hdoc_tmp_file", num);
    free(num);
    return (str);
}

char **add_to_list(char **list, char *item) {
    int count = 0;
    char **new_list;

    while (list && list[count])
        count++;
    new_list = malloc(sizeof(char *) * (count + 2));
    if (!new_list)
        return NULL;
    for (int i = 0; i < count; i++)
        new_list[i] = list[i];
    new_list[count] = item;
    new_list[count + 1] = NULL;
    free(list);
    return new_list;
}

t_command *create_command(void) {
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->num_args = 0;
    cmd->input_files = NULL;
    cmd->output_files = NULL;
    cmd->append_output = 0;
    cmd->heredoc = 0;
    cmd->heredoc_files = NULL;
    cmd->and = 0;
    cmd->or = 0;
    cmd->parentheses = 0;
    cmd->next = NULL;
    return cmd;
}

void add_argument(t_command *cmd, char *arg) {
    cmd->args = add_to_list(cmd->args, arg);
    cmd->num_args++;
}

t_command *parse_tokens_to_commands(t_token *tokens, t_shell *shell) {
    t_command *cmd_list = NULL;
    t_command *current_cmd = NULL;
    t_token *current = tokens;

    while (current) {
        if (!current_cmd)
            current_cmd = create_command();

        if (current->type == WORD || current->type == DOUBLE_QUOTES || current->type == SINGLE_QUOTES || current->type == WILDC) {
            add_argument(current_cmd, ft_strdup(current->value));
        } else if (current->type == REDIRECT_IN || current->type == HEREDOC) {
            if (current->next && (current->next->type == WORD || current->next->type == DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES)) {
                current_cmd->input_files = add_to_list(current_cmd->input_files, ft_strdup(current->next->value));
                if (current->type == HEREDOC) {
                    current_cmd->heredoc = 1;
                    current_cmd->heredoc_files = add_to_list(current_cmd->heredoc_files, generate_filename());
                }
                current = current->next;
            }
        } else if (current->type == REDIRECT_OUT || current->type == APPEND) {
            if (current->next && (current->next->type == WORD || current->next->type == DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES)) {
                current_cmd->output_files = add_to_list(current_cmd->output_files, ft_strdup(current->next->value));
                if (current->type == APPEND)
                    current_cmd->append_output = 1;
                current = current->next;
            }
        } else if (current->type == PIPE) {
            if (cmd_list) {
                t_command *temp = cmd_list;
                while (temp->next)
                    temp = temp->next;
                temp->next = current_cmd;
            } else {
                cmd_list = current_cmd;
            }
            current_cmd = NULL;
        }
        current = current->next;
    }

    if (current_cmd) {
        if (cmd_list) {
            t_command *temp = cmd_list;
            while (temp->next)
                temp = temp->next;
            temp->next = current_cmd;
        } else {
            cmd_list = current_cmd;
        }
    }

    return cmd_list;
}

t_command *parse_tokens_to_commands(t_token *tokens, t_shell *shell) {
    t_command *cmd_list = NULL;
    t_command *current_cmd = NULL;
    t_token *current = tokens;

    while (current) {
        if (!current_cmd)
            current_cmd = create_command();

        if (current->type == WORD || current->type == DOUBLE_QUOTES || current->type == SINGLE_QUOTES || current->type == WILDC) {
            add_argument(current_cmd, ft_strdup(current->value));
        } else if (current->type == REDIRECT_IN || current->type == HEREDOC) {
            if (current->next && (current->next->type == WORD || current->next->type == DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES)) {
                current_cmd->input_files = add_to_list(current_cmd->input_files, ft_strdup(current->next->value));
                if (current->type == HEREDOC) {
                    current_cmd->heredoc = 1;
                    current_cmd->heredoc_files = add_to_list(current_cmd->heredoc_files, generate_filename());
                }
                current = current->next;
            }
        } else if (current->type == REDIRECT_OUT || current->type == APPEND) {
            if (current->next && (current->next->type == WORD || current->next->type == DOUBLE_QUOTES || current->next->type == SINGLE_QUOTES)) {
                current_cmd->output_files = add_to_list(current_cmd->output_files, ft_strdup(current->next->value));
                if (current->type == APPEND)
                    current_cmd->append_output = 1;
                current = current->next;
            }
        } else if (current->type == PIPE) {
            if (cmd_list) {
                t_command *temp = cmd_list;
                while (temp->next)
                    temp = temp->next;
                temp->next = current_cmd;
            } else {
                cmd_list = current_cmd;
            }
            current_cmd = NULL;
        }
        current = current->next;
    }

    if (current_cmd) {
        if (cmd_list) {
            t_command *temp = cmd_list;
            while (temp->next)
                temp = temp->next;
            temp->next = current_cmd;
        } else {
            cmd_list = current_cmd;
        }
    }

    return cmd_list;
}*/



// Generador de número aleatorio
static int generate_random_number(void)
{
    static unsigned int seed = 12345;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (seed % 10000);
}

char *generate_filename(void)
{
    char *str;
    char *num;
    num = ft_itoa(generate_random_number());
    str = ft_strjoin("hdoc_tmp_file", num);
    free(num);
    return (str);
}

t_command *create_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->num_args = 0;
    cmd->input_files = NULL;
    cmd->output_files = NULL;
    cmd->append_output = 0;
    cmd->heredoc = 0;
    cmd->and = 0;
    cmd->or = 0;
    cmd->parentheses = 0;
    cmd->fd = -1;
    cmd->next = NULL;
    return (cmd);
}

void add_argument(t_command *cmd, char *arg)
{
    cmd->args = ft_realloc(cmd->args, sizeof(char *) * cmd->num_args, sizeof(char *) * (cmd->num_args + 2));
    cmd->args[cmd->num_args] = ft_strdup(arg);
    cmd->num_args++;
    cmd->args[cmd->num_args] = NULL;
}

void add_input_file(t_command *cmd, char *file)
{
    int i = 0;

    while (cmd->input_files && cmd->input_files[i])
        i++;
    cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, sizeof(char *) * (i + 2));
    cmd->input_files[i] = ft_strdup(file);
    cmd->input_files[i + 1] = NULL;
}

void add_output_file(t_command *cmd, char *file, int append)
{
    int i = 0;

    while (cmd->output_files && cmd->output_files[i])
        i++;
    cmd->output_files = ft_realloc(cmd->output_files, sizeof(char *) * i, sizeof(char *) * (i + 2));
    cmd->output_files[i] = ft_strdup(file);
    cmd->output_files[i + 1] = NULL;
    cmd->append_output = append;
}

void add_heredoc_file(t_command *cmd, char *file)
{
    int i = 0;

    while (cmd->input_files && cmd->input_files[i])
        i++;
    cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * i, sizeof(char *) * (i + 2));
    cmd->input_files[i] = ft_strdup(file);
    cmd->input_files[i + 1] = NULL;
    cmd->heredoc = 1;
}

void parse_parentheses(t_token **tokens, t_command *current_cmd, t_shell *shell)
{
    t_command *sub_cmd;
    t_token *current;

    current = *tokens;
    while (current && current->type != RPAREN)
    {
        sub_cmd = create_command();
        parse_general_tokens_cmd(&current, sub_cmd, shell);
        if (!current_cmd->next)
            current_cmd->next = sub_cmd;
        else
        {
            t_command *last = current_cmd->next;
            while (last->next)
                last = last->next;
            last->next = sub_cmd;
        }
        if (current)
            current = current->next;
    }
    *tokens = current;
}

void handle_parentheses(t_token **tokens, t_command *current_cmd, t_shell *shell)
{
    current_cmd->parentheses = 1;
    parse_parentheses(tokens, current_cmd, shell);
}

void handle_word_token(t_token **current, t_command *cmd)
{
    add_argument(cmd, (*current)->value);
}

void handle_redirect_token(t_token **current, t_command *cmd, t_shell *shell, int type)
{
    *current = (*current)->next;
    while (*current && (*current)->type == SPACES)
        *current = (*current)->next;

    if (*current && (*current)->type == WORD)
    {
        if (type == REDIRECT_IN)
            add_input_file(cmd, (*current)->value);
        else if (type == REDIRECT_OUT)
            add_output_file(cmd, (*current)->value, 0);
        else if (type == APPEND)
            add_output_file(cmd, (*current)->value, 1);
    }
    else
        handle_error("syntax error: expected file after redirection", shell);
}

void parse_general_tokens_cmd(t_token **tokens, t_command *cmd, t_shell *shell)
{
    t_token *current = *tokens;

    while (current && current->type != RPAREN)
    {
        if (current->type == WORD || current->type == DOUBLE_QUOTES || current->type == SINGLE_QUOTES || current->type == WILDC)
            handle_word_token(&current, cmd);
        else if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT || current->type == APPEND)
            handle_redirect_token(&current, cmd, shell, current->type);
        else if (current->type == HEREDOC)
        {
            char *filename = generate_filename();
            add_heredoc_file(cmd, filename);
            free(filename);
        }
        else if (current->type == PIPE)
        {
            cmd->next = create_command();
            cmd = cmd->next;
        }
        else if (current->type == AND || current->type == OR)
        {
            if (current->type == AND)
                cmd->and = 1;
            else
                cmd->or = 1;
            cmd->next = create_command();
            cmd = cmd->next;
        }
        else if (current->type == LPAREN)
            handle_parentheses(&current, cmd, shell);
        current = current->next;
    }
}

void parse_tokens(t_token **tokens, t_shell *shell)
{
    t_command *current_cmd;

    current_cmd = create_command();
    shell->commands = current_cmd;
    parse_general_tokens_cmd(tokens, current_cmd, shell);
}

