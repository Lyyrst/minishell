/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:15:45 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/04 16:54:36 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get size of env struct
static int	env_size(t_env *env)
{
	int		n;
	t_env	*c;

	if (!env)
		return (0);
	n = 0;
	c = env;
	while (c)
	{
		c = c->next;
		n++;
	}
	return (n);
}

//check if key exist in copy
static int	is_printed(char *key, t_env *copy)
{
	if (!copy)
		return (0);
	while (copy)
	{
		if (ft_strcmp(key, copy->key) == 0)
			return (1);
		copy = copy->next;
	}
	return (0);
}

//print the node
static void	export_print(t_env *env)
{
	if (ft_strcmp("_", env->key) == 0)
		return ;
	if (env->print == 0)
		printf("declare -x %s\n", env->key);
	else
	{
		if (ft_strlen(env->value) == 0)
			printf("declare -x %s=\"\"\n", env->key);
		else
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
	}
}

//add the key to copy
static void	add_copy(char *key, t_env **copy)
{
	t_env	*new;
	t_env	*c;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->next = 0;
	new->print = 0;
	new->value = 0;
	if (*copy == NULL)
		(*copy) = new;
	else
	{
		c = *copy;
		while (c->next != NULL)
			c = c->next;
		c->next = new;
	}
}

//print export
void	print_export(t_env **env)
{
	t_env	*cu;
	t_env	*copy;
	int		ac;
	int		len;

	cu = *env;
	copy = 0;
	ac = 97;
	len = env_size(cu);
	while (len > env_size(copy))
	{
		while (cu)
		{
			if (((char)ac == cu->key[0] || (char)(ac - 32) == cu->key[0])
					&& is_printed(cu->key, copy) == 0)
			{
				export_print(cu);
				add_copy(cu->key, &copy);
			}
			cu = cu->next;
		}
		cu = *env;
		ac++;
	}
	free_env(copy);
}
