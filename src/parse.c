/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:29:10 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/03 15:08:37 by cgaratej         ###   ########.fr       */
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









/*static t_command *new_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->input_files = NULL;
    cmd->output_files = NULL;
    cmd->append_output = 0;
    cmd->heredoc = 0;
    cmd->and = 0;
    cmd->or = 0;
    cmd->parentheses = 0;
    cmd->next = NULL;
    return (cmd);
}

static void add_command(t_command **cmd_list, t_command *new_cmd)
{
    t_command *last;

    if (!*cmd_list)
    {
        *cmd_list = new_cmd;
        return;
    }
    last = *cmd_list;
    while (last->next)
        last = last->next;
    last->next = new_cmd;
}

static void free_command(t_command *cmd)
{
    int i;

    if (cmd->args)
    {
        for (i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }
    if (cmd->input_files)
    {
        for (i = 0; cmd->input_files[i]; i++)
            free(cmd->input_files[i]);
        free(cmd->input_files);
    }
    if (cmd->output_files)
    {
        for (i = 0; cmd->output_files[i]; i++)
            free(cmd->output_files[i]);
        free(cmd->output_files);
    }
    free(cmd);
}

static char *concat_args(char *dest, const char *src)
{
    char *new_str;

    if (!dest)
        return ft_strdup(src);
    new_str = ft_strjoin(dest, src);
    free(dest);
    return new_str;
}


#include "../includes/minishell.h"

static void handle_redirection(t_command *cmd, t_token *token, t_token *next_token)
{
    if (token->type == REDIRECT_IN)
        cmd->input_files = ft_realloc(cmd->input_files, sizeof(char *) * (ft_strlen((char *)cmd->input_files) + 2), sizeof(char *) * (ft_strlen((char *)cmd->input_files) + 2));
    else if (token->type == REDIRECT_OUT || token->type == APPEND)
    {
        cmd->output_files = ft_realloc(cmd->output_files, sizeof(char *) * (ft_strlen((char *)cmd->output_files) + 2), sizeof(char *) * (ft_strlen((char *)cmd->output_files) + 2));
        if (token->type == APPEND)
            cmd->append_output = 1;
    }
    if (next_token && next_token->type == WORD)
    {
        if (token->type == REDIRECT_IN)
            cmd->input_files[ft_strlen((char *)cmd->input_files)] = ft_strdup(next_token->value);
        else
            cmd->output_files[ft_strlen((char *)cmd->output_files)] = ft_strdup(next_token->value);
    }
}

static void handle_logical_operators(t_command *cmd, t_token *token)
{
    if (token->type == AND)
        cmd->and = 1;
    else if (token->type == OR)
        cmd->or = 1;
}

static void handle_parentheses_parser(t_command *cmd, t_token *token)
{
    if (token->type == LPAREN || token->type == RPAREN)
        cmd->parentheses = 1;
}

static void handle_word_parser(t_command *cmd, t_token *token, int *arg_count)
{
    if (!cmd->args)
        cmd->args = malloc(sizeof(char *) * 2);
    else
        cmd->args = ft_realloc(cmd->args, sizeof(char *) * (*arg_count + 1), sizeof(char *) * (*arg_count + 2));
    cmd->args[*arg_count] = ft_strdup(token->value);
    cmd->args[*arg_count + 1] = NULL;
    (*arg_count)++;
}

void parse_tokens(t_token *tokens, t_shell *shell)
{
    t_token *current_token;
    t_command *current_command;
    int arg_count;

    current_token = tokens;
    current_command = new_command();
    if (!current_command)
        handle_error(NULL, shell);
    arg_count = 0;
    while (current_token)
    {
        if (current_token->type == WORD || current_token->type == DOUBLE_QUOTES || current_token->type == SINGLE_QUOTES || current_token->type == SPACES)
        {
            handle_word_parser(current_command, current_token, &arg_count);
        }
        else if (current_token->type == REDIRECT_IN || current_token->type == REDIRECT_OUT || current_token->type == APPEND || current_token->type == HEREDOC)
        {
            handle_redirection(current_command, current_token, current_token->next);
        }
        else if (current_token->type == AND || current_token->type == OR)
        {
            handle_logical_operators(current_command, current_token);
            add_command(&shell->commands, current_command);
            current_command = new_command();
            arg_count = 0;
        }
        else if (current_token->type == LPAREN || current_token->type == RPAREN)
        {
            handle_parentheses_parser(current_command, current_token);
        }
        current_token = current_token->next;
    }
    add_command(&shell->commands, current_command);
}
*/

t_command *create_command()
{
    t_command *command = malloc(sizeof(t_command));
    if (!command)
        handle_error("malloc failed", NULL);
    command->args = NULL;
    command->num_args = 0;
    command->input_files = NULL;
    command->output_files = NULL;
    command->append_outputs = NULL;
    command->num_inputs = 0;
    command->num_outputs = 0;
    command->heredoc = 0;
    command->and = 0;
    command->or = 0;
    command->next = NULL;
    return command;
}

void add_argument(t_command *command, char *arg)
{
    command->args = realloc(command->args, sizeof(char *) * (command->num_args + 2));
    if (!command->args)
        handle_error("realloc failed", NULL);
    command->args[command->num_args] = ft_strdup(arg);
    command->args[command->num_args + 1] = NULL;
    command->num_args++;
}

void add_input_file(t_command *command, char *file)
{
    command->input_files = realloc(command->input_files, sizeof(char *) * (command->num_inputs + 2));
    if (!command->input_files)
        handle_error("realloc failed", NULL);
    command->input_files[command->num_inputs] = ft_strdup(file);
    command->input_files[command->num_inputs + 1] = NULL;
    command->num_inputs++;
}

void add_output_file(t_command *command, char *file, int append)
{
    command->output_files = realloc(command->output_files, sizeof(char *) * (command->num_outputs + 2));
    command->append_outputs = realloc(command->append_outputs, sizeof(int) * (command->num_outputs + 1));
    if (!command->output_files || !command->append_outputs)
        handle_error("realloc failed", NULL);
    command->output_files[command->num_outputs] = ft_strdup(file);
    command->output_files[command->num_outputs + 1] = NULL;
    command->append_outputs[command->num_outputs] = append;
    command->num_outputs++;
}
t_command *parse_tokens(t_token *tokens)
{
    t_command *command = create_command();
    t_command *head = command;
    t_token *current = tokens;

    while (current)
    {
        if (current->type == WORD)
        {
            add_argument(command, current->value);
        }
        else if (current->type == REDIRECT_IN)
        {
            current = current->next;
            if (!current || current->type != WORD)
                handle_error("syntax error: expected file after '<'", NULL);
            add_input_file(command, current->value);
        }
        else if (current->type == REDIRECT_OUT)
        {
            current = current->next;
            if (!current || current->type != WORD)
                handle_error("syntax error: expected file after '>'", NULL);
            add_output_file(command, current->value, 0);
        }
        else if (current->type == APPEND)
        {
            current = current->next;
            if (!current || current->type != WORD)
                handle_error("syntax error: expected file after '>>'", NULL);
            add_output_file(command, current->value, 1);
        }
        else if (current->type == HEREDOC)
        {
            current = current->next;
            if (!current || current->type != WORD)
                handle_error("syntax error: expected delimiter after '<<'", NULL);
            command->heredoc = 1;
            // Aquí deberíamos manejar el heredoc real leyendo hasta el delimitador
        }
        else if (current->type == PIPE)
        {
            command->next = create_command();
            command = command->next;
        }
        else if (current->type == AND)
        {
            command->and = 1;
            command->next = create_command();
            command = command->next;
        }
        else if (current->type == OR)
        {
            command->or = 1;
            command->next = create_command();
            command = command->next;
        }
        current = current->next;
    }
    return head;
}
void handle_heredocs(t_command *command)
{
    if (command->heredoc)
    {
        // Crear archivo temporal para heredoc
        char template[] = "/tmp/heredocXXXXXX";
        int fd = mkstemp(template);
        if (fd == -1)
            handle_error("mkstemp failed", NULL);

        // Leer hasta el delimitador y escribir en el archivo temporal
        char *line;
        while (1)
        {
            line = readline("> ");
            if (ft_strcmp(line, command->args[0]) == 0) // Suponiendo que el delimitador está en args[0]
                break;
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
        close(fd);
        add_input_file(command, template);
        command->heredoc = 0; // Resetear el flag heredoc
    }
}

t_command *parse_parentheses(t_token **current)
{
    t_command *sub_command = create_command();
    t_command *head = sub_command;

    while (*current && (*current)->type != RPAREN)
    {
        if ((*current)->type == LPAREN)
        {
            *current = (*current)->next;
            sub_command->next = parse_parentheses(current);
        }
        else
        {
            // Manejar tokens como se hace en parse_tokens
        }
        *current = (*current)->next;
    }
    if (!(*current))
        handle_error("syntax error: unmatched '('", NULL);
    return head;
}

t_command *parse_tokens_with_parentheses(t_token *tokens)
{
    t_command *command = create_command();
    t_command *head = command;
    t_token *current = tokens;

    while (current)
    {
        if (current->type == LPAREN)
        {
            current = current->next;
            command->next = parse_parentheses(&current);
        }
        else
        {
            // Manejar tokens como en parse_tokens
        }
        current = current->next;
    }
    return head;
}*/

*/
