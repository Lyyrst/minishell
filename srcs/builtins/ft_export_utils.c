/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:19 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/05 16:05:50 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_upadte_env(char *value, char *key, t_env **env, int n)
{
	t_env	*ptr;

	ptr = *env;
	if (search_in_env(key, ptr))
	{
		while (ptr)
		{
			if (ft_strcmp(ptr->key, key) == 0)
			{
				free(ptr->value);
				free(key);
				ptr->print = n;
				ptr->value = value;
				return ;
			}
			ptr = ptr->next;
		}
	}
	else
		ft_env_add_back(env, ft_env_new(key, value, n));
}

//is there an equal in export command ?
int	is_equal(char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '=')
			ret = 1;
		i++;
	}
	return (ret);
}

static int	append_env_expand(char *value, char *key, t_env **env)
{
	t_env	*ptr;
	char	*tmp;

	ptr = *env;
	tmp = 0;
	if (search_in_env(key, ptr))
	{
		while (ptr)
		{
			if (ft_strcmp(ptr->key, key) == 0)
			{
				tmp = ptr->value;
				ptr->value = ft_strjoin(ptr->value, value);
				free(tmp);
				free(key);
				free(value);
				return (0);
			}
			ptr = ptr->next;
		}
	}
	else
		return (1);
	return (0);
}

//append the env instend of replace it
void	append_env(char *value, char *old_key, t_env **env, int n)
{
	char	*key;

	key = old_key;
	if (old_key)
	{
		key = ft_strtrim(old_key, "+");
		free(old_key);
	}
	if (append_env_expand(value, key, env))
		ft_env_add_back(env, ft_env_new(key, value, n));
}
