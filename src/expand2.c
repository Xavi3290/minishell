/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:22:32 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/06/20 16:35:47 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *name, t_shell *shell)
{
	int		i;
	char	*env_name;
	size_t	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		env_name = shell->env[i];
		if (ft_strncmp(env_name, name, name_len) == 0
			&& env_name[name_len] == '=')
			return (ft_strdup(env_name + name_len + 1));
		i++;
	}
	return (ft_strdup(""));
}
/*
static char	*expand_special_variable(char *var, t_shell *shell)
{
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(shell->last_exit_status));
	return (get_env_value(var, shell));
}
*/

static char	*expand_special_variable(char *expanded, t_shell *shell, int *i)
{
	char	*env_value;
	char	*tmp;

	env_value = ft_itoa(shell->last_exit_status);
	tmp = expanded;
	expanded = ft_strjoin(expanded, env_value);
	free(tmp);
	free(env_value);
	(*i)++;
	return (expanded);
}

/*
char	*expand_variable(char *str, t_shell *shell)
{
	char	*expanded;
	char	*tmp;
	char	*env_value;
	char	*joined;
	int		i;
	int		j;

	i = 0;
	expanded = handle_dollar_signs(str, i);
	while (str[i])
	{
		if (str[i] == '$')
		{
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
				continue ;
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
		}
		else
		{
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

*/

static char	*expand_special_variables(char *expanded, char *str, t_shell *shell,
		int *i)
{
	char	*env_value;
	char	*tmp;
	int		j;

	j = *i;
	if (str[*i] == '?')
		expanded = expand_special_variable(expanded, shell, i);
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		tmp = ft_substr(str, j, *i - j);
		env_value = get_env_value(tmp, shell);
		free(tmp);
		tmp = expanded;
		expanded = ft_strjoin(expanded, env_value);
		free(tmp);
		free(env_value);
	}
	return (expanded);
}

static char	*expand_general_variable(char *expanded, char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*joined;

	j = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, j, *i - j);
	joined = ft_strjoin(expanded, tmp);
	free(expanded);
	expanded = joined;
	free(tmp);
	return (expanded);
}

char	*expand_variable(char *str, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	expanded = handle_dollar_signs(str, i);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			expanded = expand_special_variables(expanded, str, shell, &i);
		}
		else
			expanded = expand_general_variable(expanded, str, &i);
	}
	return (expanded);
}
