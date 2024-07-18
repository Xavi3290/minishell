/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:23:12 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/18 14:46:20 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_variable_token(t_token **tokens, t_shell *shell,
		t_token **current, t_token **prev)
{
	char	*expanded;
	t_token	*new_tokens;

	expanded = expand_variable((*current)->value, shell);
	if (expanded && expanded[0] != '\0')
	{
		new_tokens = tokenize(expanded, shell);
		insert_tokens(tokens, new_tokens, *prev, *current);
		if (*prev)
			*current = (*prev)->next;
		else
			*current = *tokens;
		free(expanded);
	}
}

void	expand_double_quotes_token(t_token *current, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(current->value, shell);
	if (expanded)
	{
		free(current->value);
		current->value = expanded;
	}
}

void	expand_wildcard_token(t_token **tokens, t_shell *shell,
		t_token **current, t_token **prev)
{
	char	**expansions;
	t_token	*new_tokens;

	expansions = expand_wildcards((*current)->value, shell);
	if (expansions)
	{
		new_tokens = strings_to_tokens(expansions);
		insert_tokens(tokens, new_tokens, *prev, *current);
		if (*prev)
			*current = (*prev)->next;
		else
			*current = *tokens;
	}
}

void	expand_tokens(t_token **tokens, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;

	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD && ft_strchr(current->value, '$'))
		{
			expand_variable_token(tokens, shell, &current, &prev);
		}
		else if (current->type == DOUBLE_QUOTES && ft_strchr(current->value, \
			'$'))
		{
			expand_double_quotes_token(current, shell);
		}
		else if (current->type == WORD && ft_strchr(current->value, '*'))
		{
			expand_wildcard_token(tokens, shell, &current, &prev);
		}
		prev = current;
		current = current->next;
	}
}

t_token	*tokenize_and_expand(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = tokenize(line, shell);
	if (!tokens)
		return (NULL);
	expand_tokens(&tokens, shell);
	join_adjacent_tokens(&tokens);
	return (tokens);
}















/*t_token	*tokenize_and_expand(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = tokenize(line, shell);
	if (!tokens)
		return (NULL);
	expand_tokens(&tokens, shell);
	join_adjacent_tokens(&tokens);
	if (!check_syntax(tokens, shell))
    {
        free_tokens(tokens);
        free(shell->line);
        shell->line = NULL;
        return (NULL);
    }
	parse_tokens(&tokens, shell);
    //execute_commands(shell);
	return (tokens);
}*/


t_token	*tokenize_and_expand_segment(char *segment, t_shell *shell)
{
	t_token *tokens = tokenize(segment, shell);
	if (!tokens)
		return (NULL);
	expand_tokens(&tokens, shell);
	join_adjacent_tokens(&tokens);
	if (!check_syntax(tokens, shell))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

void execute_segment(char *segment, t_shell *shell)
{
	t_token *tokens = tokenize_and_expand_segment(segment, shell);
	if (tokens)
	{
		parse_tokens(&tokens, shell);
		execute_commands(shell);
		free_tokens(tokens);
	}
}

/*int is_logical_operator(t_token *token)
{
	return (token->type == AND || token->type == OR);
}*/


int count_segments(t_token *tokens)
{
	t_token *current = tokens;
	int count = 1;  // Al menos un segmento

	while (current)
	{
		if (current->type == AND || current->type == OR)
			count++;
		current = current->next;
	}
	return count;
}

char **extract_segments(t_token *tokens, char *line, int count)
{
	char **segments = malloc(sizeof(char *) * (count + 1));
	if (!segments)
		handle_error(NULL, NULL);

	t_token *current = tokens;
	char *segment_start = line;
	int segment_index = 0;

	while (current)
	{
		if (current->type == AND || current->type == OR)
		{
			int len = current->value - segment_start;
			segments[segment_index] = ft_strndup(segment_start, len);
			segment_start = current->value + ft_strlen(current->value);
			segment_index++;
		}
		current = current->next;
	}

	segments[segment_index] = ft_strdup(segment_start);
	segments[segment_index + 1] = NULL;
	return segments;
}

char **split_by_logical_operators(char *line, t_shell *shell)
{
	t_token *tokens = tokenize(line, shell);
	if (!tokens)
		return NULL;

	int count = count_segments(tokens);
	char **segments = extract_segments(tokens, line, count);
	
	free_tokens(tokens);
	return (segments);
}


void execute_segments(char **segments, t_shell *shell)
{
	int i = 0;
	while (segments[i])
	{
		execute_segment(segments[i], shell);
		if ((shell->last_exit_status == 0 && shell->commands->and) ||
			(shell->last_exit_status != 0 && shell->commands->or))
		{
			i++;
		}
		else
		{
			break;
		}
		i++;
	}
}

void tokenize_expand_cmd_execute(char *line, t_shell *shell)
{
	char **segments = split_by_logical_operators(line, shell);
	if (!segments)
		return;

	execute_segments(segments, shell);

	int i = 0;
	while (segments[i])
	{
		free(segments[i]);
		i++;
	}
	free(segments);
}
