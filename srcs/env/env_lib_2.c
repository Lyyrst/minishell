/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:41:14 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:28:51 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envvar(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**error(char **envp, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(envp[j]);
		j++;
	}
	free(envp);
	return (NULL);
}

void	complete_environment(t_env **env)
{
	char	*key;
	char	*value;

	key = ft_strdup("PWD");
	value = getcwd(NULL, 0);
	ft_env_add_back(env, ft_env_new(key, value, ft_strlen(value)));
	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	ft_env_add_back(env, ft_env_new(key, value, ft_strlen(value)));
	key = ft_strdup("_");
	value = ft_strdup("/usr/bin/env");
	ft_env_add_back(env, ft_env_new(key, value, ft_strlen(value)));
}

/**
 * Converts a chained environment list 
 * into an array of strings.
 *
 * @param env	A pointer to the environment linked list structure.
 * @return		An array of strings representing the environment.
 * 				The last element of the array is NULL.
 * 				On error, NULL is returned.
 */
char	**ft_env_to_array(t_env *env)
{
	char	**envp;
	t_env	*current;
	int		count;
	int		i;

	i = 0;
	current = env;
	count = count_envvar(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = env;
	while (current)
	{
		envp[i] = malloc(strlen(current->key) + ft_strlen(current->value) + 2);
		if (!envp[i])
			return (error(envp, i));
		ft_strcpy(envp[i], current->key);
		envp[i][ft_strlen(current->key)] = '=';
		ft_strcpy(envp[i] + ft_strlen(current->key) + 1, current->value);
		current = current->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}
