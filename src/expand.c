/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:23:12 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/19 15:42:45 by xroca-pe         ###   ########.fr       */
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
                i = 0; // Inicialización del índice para el bucle while
                while (expansions[i]) {
                    new_tok = new_token(WORD, expansions[i]);
                    if (prev)
                        prev->next = new_tok;
                    else
                        *tokens = new_tok;
                    prev = new_tok;
                    i++; // Actualización del índice
                }
                prev->next = current->next;
                free(current->value);
                free(current);
                current = prev;
                while (expansions[i])
                {
                    free(expansions[i]);
                    i++;
                }
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






static char *handle_dollar_signs(char *str, int i) {
    int dollar_count = 0;
    char *dollar_str;
    char *dup;
    

    while (str[i] == '$') {
        dollar_count++;
        i++;
    }

    if (dollar_count > 1) {
        dollar_str = malloc(dollar_count);
        if (!dollar_str)
            return (NULL);
        memset(dollar_str, '$', dollar_count - 1);
        dollar_str[dollar_count - 1] = '\0';
        //return (ft_strdup(dollar_str));
        //add_token(tokens_list, new_token(WORD, ft_strdup(dollar_str)));
        //free(dollar_str);
        dup = ft_strdup(dollar_str);
        return (dup);
    }
    return (ft_strdup(""));
}


static char *get_env_value(char *name, t_shell *shell) {
    int i;
    char *env_name;
    size_t name_len;

    name_len = ft_strlen(name);
    i = 0;
    while (shell->env[i]) {
        env_name = shell->env[i];
        if (ft_strncmp(env_name, name, name_len) == 0 && env_name[name_len] == '=')
            return (ft_strdup(env_name + name_len + 1));
        i++;
    }
    return (ft_strdup(""));
}

static char *expand_special_variable(char *var, t_shell *shell) {
    if (ft_strcmp(var, "?") == 0) {
        return ft_itoa(shell->last_exit_status);
    }
    return get_env_value(var, shell);
}

char *expand_variable(char *str, t_shell *shell) {
    char *expanded;
    char *tmp;
    char *env_value;
    char *joined;
    int i; 
    int j;

    i = 0;
    expanded = handle_dollar_signs(str, i);

    //expanded = ft_strdup("");
    while (str[i]) {
        if (str[i] == '$') {
            i++;
            j = i;
            if (str[j] == '?')
            {
                env_value = expand_special_variable("?", shell);
                tmp = expanded;
                expanded = ft_strjoin(expanded, env_value);
                free(tmp);
                free(env_value);
                i++;
                continue;
            }
            while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
                j++;
            tmp = ft_substr(str, i, j - i);
            env_value = get_env_value(tmp, shell);
            free(tmp);
            tmp = expanded;
            expanded = ft_strjoin(expanded, env_value);
            
            free(tmp);
            free(env_value);
            i = j;
        } else {
            j = i;
            while (str[i] && str[i] != '$')
                i++;
            tmp = ft_substr(str, j, i - j);
            joined = ft_strjoin(expanded, tmp);
            free(expanded);
            expanded = joined;
            free(tmp);
        }
    }
    return (expanded);
}


int match(const char *pattern, const char *str) {
    if (*pattern == '\0' && *str == '\0')
        return 1;
    if (*pattern == '*') {
        if (match(pattern + 1, str) || (*str && match(pattern, str + 1)))
            return 1;
    } else if (*pattern == *str) {
        return match(pattern + 1, str + 1);
    }
    return 0;
}


static char **append_match(char **matches, int *count, const char *match) {
    char **new_matches;
    int i;

    new_matches = malloc(sizeof(char *) * (*count + 2));
    if (!new_matches)
        return NULL;
    i = 0;
    while (i < *count) {
        new_matches[i] = matches[i];
        i++;
    }
    new_matches[i] = ft_strdup(match);
    if (!new_matches[i])
        return NULL;
    new_matches[i + 1] = NULL;
    free(matches);
    *count += 1;
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
        if (match(pattern, entry->d_name)) {
            matches = append_match(matches, &count, entry->d_name);
            if (!matches) {
                closedir(dir);
                return NULL;
            }
        }
    }
    closedir(dir);
    return matches;
}



/*
// Función auxiliar para comparar un patrón con un nombre de archivo
int match_pattern(const char *pattern, const char *filename) {
    while (*pattern && *filename) {
        if (*pattern == '*') {
            pattern++;
            while (*filename && *filename != *pattern) {
                filename++;
            }
        } else if (*pattern == *filename) {
            pattern++;
            filename++;
        } else {
            return 0;
        }
    }
    return (*pattern == '\0' && *filename == '\0');
}

// Función para expandir wildcards en el directorio actual
char **expand_wildcards(const char *pattern) {
    DIR *dir;
    struct dirent *entry;
    char **matches = NULL;
    int count = 0;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (match_pattern(pattern, entry->d_name)) {
            matches = ft_realloc(matches, sizeof(char *) * (count + 2));
            matches[count] = ft_strdup(entry->d_name);
            count++;
        }
    }
    closedir(dir);

    if (matches) {
        matches[count] = NULL;
    }
    return matches;
}

*/

void insert_tokens(t_token **tokens, t_token *new_tokens, t_token *prev, t_token *current) {
    t_token *last_new;

    if (!new_tokens)
        return;

    last_new = new_tokens;
    while (last_new->next)
        last_new = last_new->next;

    if (prev)
        prev->next = new_tokens;
    else
        *tokens = new_tokens;

    last_new->next = current->next;
    free(current->value);
    free(current);
}


void expand_tokens(t_token **tokens, t_shell *shell) {
    t_token *current = *tokens;
    t_token *prev = NULL;
    t_token *new_tok;
    t_token *new_tokens;
    char **expansions;
    
    int i;
    char *expanded;

    while (current) {
        if (current->type == WORD && ft_strchr(current->value, '$')) {
            expanded = expand_variable(current->value, shell);
            if (expanded && expanded[0] != '\0') {
                new_tokens = tokenize(expanded, shell);
                insert_tokens(tokens, new_tokens, prev, current);
                if (prev)
                    current = prev->next;
                else
                    current = *tokens;
                continue;
            }
        }else if (current->type == DOUBLE_QUOTES && ft_strchr(current->value, '$'))
        {
            expanded = expand_variable(current->value, shell);
            if (expanded)
            {
                free(current->value);
                current->value = expanded;
            }
        }        
        else if (current->type == WORD && ft_strchr(current->value, '*')) {
            expansions = expand_wildcards(current->value);
            if (expansions) {
                i = 0;
                while (expansions[i]) {
                    new_tok = new_token(WORD, expansions[i]);
                    if (prev)
                        prev->next = new_tok;
                    else
                        *tokens = new_tok;
                    prev = new_tok;
                    i++;
                }
                prev->next = current->next;
                free(current->value);
                free(current);
                current = prev->next;
                i = 0;
                while (expansions[i]) {
                    free(expansions[i]);
                    i++;
                }
                free(expansions);
                continue;
            }
        }
        prev = current;
        current = current->next;
    }
}








/*TESTS*/





t_token *tokenize_and_expand(char *line, t_shell *shell) {
    t_token *tokens = tokenize(line, shell);
    if (!tokens)
        return NULL;
    expand_tokens(&tokens, shell);
    return (tokens);
}



