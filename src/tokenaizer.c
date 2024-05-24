/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenaizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:05:46 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/23 19:04:36 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
static t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

static void add_token(t_token **tokens, t_token *new_token)
{
    t_token *last;

    if (!*tokens)
    {
        *tokens = new_token;
        return ;
    }
    last = *tokens;
    while (last->next)
        last = last->next;
    last->next = new_token;
}

static void free_tokens(t_token *tokens)
{
    t_token *token;
    t_token *next;

    token = tokens;
    while (token)
    {
        next = token->next;
        free(token->value);
        free(token);
        token = next;
    }
}

static t_token *tokenize(char *line)
{
    t_token *tokens;
    t_token *token;
    char *value;
    int i;
    int j;

    tokens = NULL;
    i = 0;
    while (line[i])
    {
        if (line[i] == '|')
            token = new_token(PIPE, ft_strdup("|"));
        else if (line[i] == '<' && line[i + 1] == '<')
            token = new_token(REDIRECT_IN, ft_strdup("<"));
        else if (line[i] == '>' && line[i + 1] == '>')
            token = new_token(REDIRECT_OUT, ft_strdup(">"));
        else if (line[i] == '<')
            token = new_token(REDIRECT_IN, ft_strdup("<"));
        else if (line[i] == '>')
            token = new_token(REDIRECT_OUT, ft_strdup(">"));
        else if (line[i] == '\'')
        {
            i++;
            value = ft_strdup(&line[i]);
            j = 0;
            while (line[i] && line[i] != '\'')
            {    
                j++;
                i++;
            }
            value[j] = '\0';
            token = new_token(WORD, value);
        }            
        else if (line[i] == '"')
        {
            i++;
            value = ft_strdup(&line[i]);
            j = 0;
            while (line[i] && line[i] != '"')
            {    
                j++;
                i++;
            }
            value[j] = '\0';
            token = new_token(WORD, value);
        }            
        else if (line[i] == ' ' && line[i] == '\n' && line[i] == '\t' && line[i] == '\v' && line[i] == '\f' && line[i] == '\r')
        {
            i++;
            continue ;
        }
        else
        {
            value = ft_strdup(&line[i]);
            j = 0;
            while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>' && line[i] != '\'' && line[i] != '"')
            {    
                j++;
                i++;
            }
            value[j] = '\0';
            token = new_token(WORD, value);
        }
        add_token(&tokens, token);
        i++;
    }
    return (tokens);
}

*/
