/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/25 14:14:12 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_alphanum(char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (key[i])
	{
		if (i == len - 1 && (ft_isalnum(key[i]) || key[i] == '+' \
				|| key[i] == '_'))
			break ;
		else if (!(ft_isalnum(key[i])) && key[i] != '_')
		{
			ft_putstr_fd("bash : export: not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

// a refaire accepte que _alphadigit 
int	is_valide_identifier(char *key)
{
	if (!key || ft_strlen(key) == 0)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (key[ft_strlen(key) - 1] == '-' || ft_isdigit(key[0]))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (is_alphanum(key))
		return (1);
	return (0);
}

//check if the key contain a '+' at the end and remove it
static int	get_key(char **key, char *str)
{
	int	ret;

	ret = 0;
	if (ft_strchr(str, '+') != NULL)
	{
		ret = 1;
	}
	*key = str;
	return (ret);
}

//split export function in 2 for norm
static int	to_env(t_env **env, char **args, char **tab)
{
	int		n;
	int		append;
	char	*key;
	char	*value;

	n = is_equal(*args);
	key = 0;
	append = get_key(&key, tab[0]);
	if (is_valide_identifier(key))
		return (1);
	if (tab[1])
		value = tab[1];
	else
		value = "";
	if (append == 0)
		export_upadte_env(ft_strdup(value), ft_strdup(key), env, n);
	else
		append_env(ft_strdup(value), ft_strdup(key), env, n);
	return (0);
}

// export
int	ft_export(char **args, t_env **env)
{
	char	**split_export;
	int		code;

	code = 0;
	if (!args || !*args)
		return (1);
	args++;
	if (!*args)
		print_export(env);
	else if (ft_strcmp(*args, "=") == 0)
	{
		ft_putstr_fd("bash : export: `=': not a valid identifier\n", 2);
		return (1);
	}
	while (*args)
	{
		split_export = ft_split_export(*args);
		if (!split_export || !split_export[0])
			return (1);
		if (to_env(env, args, split_export))
			code = 1;
		args++;
		ft_free_tab(split_export);
	}
	return (code);
}
