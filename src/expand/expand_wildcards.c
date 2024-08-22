/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:23:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/22 16:50:19 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static int	match_pattern(const char *pattern, const char *filename)
{
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			pattern++;
			while (*filename && *filename != *pattern)
				filename++;
		}
		else if (*pattern == *filename)
		{
			pattern++;
			filename++;
		}
		else
			return (0);
	}
	return (*pattern == '\0' && *filename == '\0');
}*/
static int	match_pattern(const char *pattern, const char *filename)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*filename && !match_pattern(pattern, filename))
				filename++;
			if (*filename == '\0')
				return (0);
		}
		else if (*pattern == *filename)
		{
			pattern++;
			filename++;
		}
		else
			return (0);
	}
	return (*filename == '\0');
}

/*static char	**read_directory(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			matches = ft_realloc(matches, sizeof(char *) * (count + 1),
					sizeof(char *) * (count + 2));
			if (!matches)
				handle_error(NULL, NULL);
			matches[count] = ft_strdup(entry->d_name);
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (matches)
		matches[count] = NULL;
	return (matches);
}*/
static char	**get_matching_files(char **matches, int *count,
		const char *pattern, const char *filename)
{
	if (match_pattern(pattern, filename))
	{
		matches = ft_realloc(matches, sizeof(char *) * (*count + 1),
				sizeof(char *) * (*count + 2));
		if (!matches)
			handle_error(NULL, NULL);
		matches[*count] = ft_strdup(filename);
		(*count)++;
	}
	return (matches);
}

static char	**read_directory(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			matches = get_matching_files(matches, &count, pattern,
					entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (matches)
		matches[count] = NULL;
	return (matches);
}

char	**expand_wildcards(const char *pattern, t_shell *shell)
{
	DIR		*dir;
	char	**matches;

	dir = opendir(".");
	if (!dir)
	{
		handle_error("opendir", shell);
		return (NULL);
	}
	matches = read_directory(dir, pattern);
	return (matches);
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
	free_string_array(expansions);
}
