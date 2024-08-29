/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:55 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:29:23 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		(*lst) = new;
	else
	{
		last = ft_env_last(*lst);
		last->next = new;
	}
}

t_env	*ft_env_new(char *key, char *value, int n)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->key = key;
	element->value = value;
	element->next = NULL;
	if (n == 0)
		element->print = 0;
	else
		element->print = 1;
	return (element);
}

/**
 * Concatenates an array of strings into a single 
 * a single string.
 *
 * @param strings 	The string array to concatenate.
 * 					The last element of the array must be NULL.
 * @return 			A string resulting from the concatenation of the 
 * 					of the strings in the array. In the event of an error 
 * 					or if the array is empty, NULL is returned.
 */
char	*concatenate_strings(char **strings)
{
	int		total_length;
	char	*result;
	int		i;
	int		j;
	int		index;

	total_length = get_total_lenght(strings);
	i = ft_arraylen(strings);
	result = (char *)malloc(sizeof(char) * (total_length + i + 1));
	if (!result)
		return (NULL);
	total_length += i + 1;
	index = 0;
	i = 0;
	while (strings[i])
	{
		j = 0;
		while (strings[i][j])
			result[index++] = strings[i][j++];
		i++;
		if (strings[i] != 0)
			result[index++] = '=';
	}
	result[index] = '\0';
	return (result);
}

t_env	*ft_env_to_struct(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	char	**tmp;

	env = NULL;
	if (!envp || !*envp)
	{
		complete_environment(&env);
		return (env);
	}
	while (*envp)
	{
		tmp = ft_split(*envp, '=');
		if (!tmp)
			return (NULL);
		key = ft_strdup(tmp[0]);
		value = concatenate_strings(&tmp[1]);
		ft_free_tab(tmp);
		ft_env_add_back(&env, ft_env_new(key, value, ft_strlen(value)));
		envp++;
	}
	return (env);
}
