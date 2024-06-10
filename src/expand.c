/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:23:12 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/10 15:20:05 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static char *expand_variable(char *str, t_shell *shell) {
    char *var_name;
    char *value;
    char *expanded;

    var_name = str + 1; // Ignorar el '$'
    if (ft_strcmp(var_name, "?") == 0) {
        expanded = ft_itoa(shell->last_exit_status);
    } else {
        value = getenv(var_name);
        if (value)
            expanded = ft_strdup(value);
        else
            expanded = ft_strdup("");
    }
    return expanded;
}

static char **append_match(char **matches, int *count, char *match) {
    char **new_matches;

    new_matches = ft_realloc(matches, sizeof(char *) * (*count), sizeof(char *) * (*count + 2));
    if (!new_matches)
        return NULL;
    new_matches[*count] = ft_strdup(match);
    if (!new_matches[*count])
        return NULL;
    (*count)++;
    new_matches[*count] = NULL;
    return new_matches;
}

static char **expand_wildcards(char *pattern) {
    DIR *dir;
    struct dirent *entry;
    char **matches = NULL;
    int count = 0;

    dir = opendir(".");
    if (!dir)
        return NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
        if (fnmatch(pattern, entry->d_name, 0) == 0) {
            matches = append_match(matches, &count, entry->d_name);
            if (!matches)
                return NULL;
        }
    }
    closedir(dir);
    return matches;
}

static void expand_tokens(t_token **tokens, t_shell *shell) {
    t_token *current = *tokens;
    t_token *prev = NULL;
    t_token *new_tok;
    char **expansions;
    int i;

    while (current) {
        if (current->type == WORD && current->value[0] == '$') {
            char *expanded = expand_variable(current->value, shell);
            free(current->value);
            current->value = expanded;
        } else if (current->type == WORD && ft_strchr(current->value, '*')) {
            expansions = expand_wildcards(current->value);
            if (expansions) {
                for (i = 0; expansions[i]; i++) {
                    new_tok = new_token(WORD, expansions[i]);
                    if (prev)
                        prev->next = new_tok;
                    else
                        *tokens = new_tok;
                    prev = new_tok;
                }
                prev->next = current->next;
                free(current->value);
                free(current);
                current = prev;
                while (expansions[i]) free(expansions[i++]);
                free(expansions);
            }
        }
        prev = current;
        current = current->next;
    }
}

t_token *tokenize_and_expand(char *line, t_shell *shell) {
    t_token *tokens = tokenize(line, shell);
    if (!tokens)
        return NULL;
    expand_tokens(&tokens, shell);
    return tokens;
}
*/

