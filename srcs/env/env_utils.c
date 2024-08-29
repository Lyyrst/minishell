/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:41:45 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 00:56:28 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var_in_env(char *key_value, char *key, t_env *env, int n)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) - 1) == 0)
		{
			free(env->value);
			env->print = n;
			env->value = key_value;
			return ;
		}
		env = env->next;
	}
}

int	search_var_in_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) - 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	remove_var_in_env(char *key, t_env **env)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env;
	if (remove_var_if_first(key, env))
		return ;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	upadte_env(char *value, char *key, t_env *env, int n)
{
	if (search_var_in_env(key, env))
		update_var_in_env(value, key, env, n);
	else
		ft_env_add_back(&env, ft_env_new(key, value, n));
}

char	*ft_getenv(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
