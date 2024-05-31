/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/31 15:18:41 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static t_command *new_command(void)
{
    t_command *cmd;
    
    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = 0;
    cmd->heredoc = 0;
    cmd->and = 0;
    cmd->or = 0;
    cmd->parentheses = 0;
    cmd->next = NULL;
    return (cmd);    
}

static void add_command(t_command **cmd, t_command *new)
{
    t_command *last;

    if (!*cmd)
    {
        *cmd = new;
        return ;
    }
    last = *cmd;
    while (last->next)
        last = last->next;
    last->next = new;
}

static void free_command(t_command *commands)
{
    t_command *cmd;
    t_command *next;
    
    cmd = commands;
    while (cmd)
    {
        next = cmd->next;
        free(cmd->args);
        free(cmd->input_file);
        free(cmd->output_file);
        free(cmd);
        cmd = next;
    }
}

void parse_word(t_command *current_command, t_token **tokens, int *arg_count)
{
    t_token *token = *tokens;
    char *combined_value;
    char *temp;
    t_token *next_token;

    combined_value = ft_strdup(token->value);
    if (!combined_value)
        handle_error(NULL, NULL);

    next_token = token->next;
    while (next_token && 
           (next_token->type == WORD || next_token->type == SINGLE_QUOTES || next_token->type == DOUBLE_QUOTES) && 
           !ft_is_space(next_token->value[0]))
    {
        temp = combined_value;
        combined_value = ft_strjoin(combined_value, next_token->value);
        free(temp);
        if (!combined_value)
            handle_error(NULL, NULL);
        token = next_token;
        next_token = next_token->next;
    }

    current_command->args = ft_realloc(current_command->args, sizeof(char *) * (*arg_count + 1), sizeof(char *) * (*arg_count + 2));
    if (!current_command->args)
        handle_error(NULL, NULL);
    current_command->args[*arg_count] = combined_value;
    current_command->args[*arg_count + 1] = NULL;
    (*arg_count)++;
    *tokens = token;
}

int parse_redirection(t_command *current_command, t_token **tokens)
{
    t_token *token = *tokens;
    if (!token->next)
        return 0;

    if (token->type == REDIRECT_IN)
    {
        free(current_command->input_file);
        current_command->input_file = ft_strdup(token->next->value);
    }
    else if (token->type == REDIRECT_OUT)
    {
        free(current_command->output_file);
        current_command->output_file = ft_strdup(token->next->value);
        current_command->append_output = 0;
    }
    else if (token->type == APPEND)
    {
        free(current_command->output_file);
        current_command->output_file = ft_strdup(token->next->value);
        current_command->append_output = 1;
    }
    else if (token->type == HEREDOC)
    {
        free(current_command->input_file);
        current_command->input_file = ft_strdup(token->next->value);
        current_command->heredoc = 1;
    }
    else
        return 0;
    *tokens = token->next;
    return 1;
}

int parse_parentheses(t_command *current_command, t_token **tokens)
{
    t_token *token = *tokens;
    if (token->type == LPAREN)
        current_command->parentheses = 1;
    else if (token->type == RPAREN)
        current_command->parentheses = 0;
    *tokens = token->next;
    return 1;
}

t_command *parse_tokens(t_token *tokens, t_shell *shell)
{
    t_command *commands = NULL;
    t_command *current_command = NULL;
    int arg_count = 0;

    while (tokens)
    {
        if (tokens->type == WORD || tokens->type == SINGLE_QUOTES || tokens->type == DOUBLE_QUOTES)
        {
            if (!current_command)
                current_command = new_command();
            parse_word(current_command, &tokens, &arg_count);
        }
        else if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT || tokens->type == APPEND || tokens->type == HEREDOC)
        {
            if (!current_command)
                current_command = new_command();
            if (!parse_redirection(current_command, &tokens))
                return (free_commands(commands), NULL);
        }
        else if (tokens->type == PIPE || tokens->type == AND || tokens->type == OR)
        {
            if (!current_command)
                return (free_commands(commands), NULL);
            add_command(&commands, current_command);
            current_command = new_command();
            arg_count = 0;
        }
        else if (tokens->type == LPAREN || tokens->type == RPAREN)
        {
            if (!current_command)
                current_command = new_command();
            if (!parse_parentheses(current_command, &tokens))
                return (free_commands(commands), NULL);
        }
        tokens = tokens->next;
    }
    if (current_command)
        add_command(&commands, current_command);
    return commands;
}*/
    