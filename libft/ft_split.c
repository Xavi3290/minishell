/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:09:28 by cgaratej          #+#    #+#             */
/*   Updated: 2024/04/09 13:17:08 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			while (s[i] && s[i] == c)
				i++;
	}
	return (count);
}

static char	**free_words(char **words, int word_index)
{
	while (word_index)
	{
		word_index--;
		free(words[word_index]);
	}
	free(words);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		start;
	int		j;

	if (!s)
		return (0);
	words = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!words)
		return (0);
	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		words[j] = ft_substr(s, start, i - start);
		if (!words[j])
			return (free_words(words, j));
		j++;
	}
	return (words);
}

/*#include <stdio.h>

int main(void)
{
	char **words = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
	while (*words)
		printf("%s\n", *words++);
	return (0);
}*/