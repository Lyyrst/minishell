/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:23:37 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/02 17:42:13 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_seplen(char *str)
{
	int	n;

	n = 0;
	while (str[n] && str[n] != '=')
		n++;
	return (n);
}

static char	*ft_copy_first(char *str, int n)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * n + 1);
	if (!ret)
		return (0);
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*ft_copy_second(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	ret = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = '\0';
	return (ret);
}

char	**ft_split_export(char *str)
{
	char	**tab;
	int		tab_len;

	tab_len = 1;
	if (is_equal(str))
		tab_len = 2;
	tab = malloc(sizeof(char *) * (tab_len + 1));
	if (!tab)
		return (0);
	tab[0] = ft_copy_first(str, ft_seplen(str));
	if (!tab[0])
	{
		free(tab);
		return (0);
	}
	if (tab_len == 2)
	{
		tab[1] = ft_copy_second(str);
		tab[2] = NULL;
	}
	else
		tab[1] = NULL;
	return (tab);
}

//custom search for export
int	search_in_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
