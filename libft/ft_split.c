/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:05:32 by igarcia2          #+#    #+#             */
/*   Updated: 2024/01/17 19:03:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	pos;

	pos = 0;
	count = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == c && pos > 0)
		{
			count++;
			s += pos + 1;
			pos = 0;
		}
		else if (s[pos] == c)
		{
			s++;
			pos = 0;
		}
		else
			pos++;
	}
	if (pos > 0)
		count++;
	return (count);
}

static char	*get_word(const char *s, int pos)
{
	char	*res;
	int		j;

	j = 0;
	res = (char *) malloc((pos + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (j < pos)
	{
		res[j] = s[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

static char	*read_word(const char *s, char c, int word)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (i > 0)
			{
				if (x == word)
					return (get_word(s, i));
				x++;
			}
			s += i + 1;
			i = 0;
		}
		else
			i++;
	}
	if (i > 0)
		return (get_word(s, i));
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		words;

	words = count_words(s, c);
	i = 0;
	result = (char **) malloc((words +1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (words > 0)
	{
		result[i] = read_word(s, c, i);
		if (result[i] == NULL)
		{
			while (i >= 0)
				free(result[i--]);
			free (result);
			return (NULL);
		}
		i++;
		words--;
	}
	result[i] = NULL;
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = " ,Hello, world, 87, how are you,,    2u , 3498";
	char	c = ' ';
	char	**res;
	int		i;

	i = 0;
	res = ft_split(str, c);
	while(res[i] != NULL)
	{
		printf("%d: %s\n", i, res[i]);
		i++;
	}
}*/
