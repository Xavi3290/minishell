/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:23:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/08/14 15:46:14 by xroca-pe         ###   ########.fr       */
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
		if (match_pattern(pattern, entry->d_name))
		{
			matches = ft_realloc(matches, sizeof(char *) * (count + 1), \
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
