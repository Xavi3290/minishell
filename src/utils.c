#include "../includes/minishell.h"

char *ft_strndup(const char *s, size_t n)
{
    char *dup = malloc(n + 1);
    if (dup)
    {
		ft_strlcpy(dup, s, n);
        dup[n] = '\0';
    }
    return dup;
}
