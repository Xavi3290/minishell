/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:55 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/05/29 19:30:57 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, n + 1);
	return (dup);
}

int ft_is_space(char line)
{
   if (line && (line == ' ' || line == '\n' || line == '\t'
            || line == '\v' || line == '\f' || line == '\r'))
        return (1);
    return (0);       
}

void *ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, original_size);
        free(ptr);
    }
    return (new_ptr);
}

void handle_error(char *message, t_shell *shell)
{
    if (message)
        printf("minishell: %s: %s\n", message, strerror(errno));
    else
	{
        perror("minishell");
		exit(errno);
	}
    shell->last_exit_status = errno;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
