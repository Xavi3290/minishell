/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:50 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/07/04 16:00:30 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	match_pattern(const char *pattern, const char *filename)
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
}

/*
char	**expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
		{
			matches = ft_realloc(matches, sizeof(char *) * (count + 1),
					sizeof(char *) * (count + 2));
			matches[count] = ft_strdup(entry->d_name);
			count++;
		}
	}
	closedir(dir);
	if (matches)
	{
		matches[count] = NULL;
	}
	return (matches);
}
*/

static char	**read_directory(DIR *dir, const char *pattern)
{
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
		{
			matches = ft_realloc(matches, sizeof(char *) * (count + 1),
					sizeof(char *) * (count + 2));
			matches[count] = ft_strdup(entry->d_name);
			count++;
		}
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
		//perror("opendir");
		handle_error("opendir", shell);
		return (NULL);
	}
	matches = read_directory(dir, pattern);
	return (matches);
}

t_token	*strings_to_tokens(char **strings)
{
	t_token	*tokens;
	t_token	*new_tok;
	int		i;

	tokens = NULL;
	i = 0;
	while (strings[i])
	{
		new_tok = new_token(WILDC, ft_strdup(strings[i]));
		if (!new_tok)
			return (NULL);
		add_token(&tokens, new_tok);
		i++;
	}
	return (tokens);
}

void	insert_tokens(t_token **tokens, t_token *new_tokens, t_token *prev,
		t_token *current)
{
	t_token	*last_new;

	if (!new_tokens)
		return ;
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
