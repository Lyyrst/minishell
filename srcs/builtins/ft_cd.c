/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:52:35 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 17:47:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valide_parsing(char **args, t_env *env)
{
	(void)env;
	if (!args || !*args)
		return (1);
	if (args[1] && args[2])
	{
		ft_putstr_fd("bash: too many arguments\n", 2);
		return (1);
	}
	if (!env)
		return (0);
	return (-1);
}

static void	update_env_pwd(t_env **env, char *old_path)
{
	char	*path;

	path = getcwd(NULL, 0);
	upadte_env(path, "PWD", *env, ft_strlen(path));
	upadte_env(old_path, "OLDPWD", *env, ft_strlen(path));
}

int	cd_back_pwd(t_env *env)
{
	int		exit_code;
	char	*path;

	path = ft_getenv("OLDPWD", env);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	path = ft_getenv("OLDPWD", env);
	exit_code = chdir(path);
	free(path);
	return (exit_code);
}

int	ft_cd_no_args(t_env *env)
{
	char	*path;
	int		exit_code;

	path = ft_getenv("HOME", env);
	exit_code = chdir(path);
	free(path);
	return (exit_code);
}

int	ft_cd(char **args, t_env *env)
{
	int		exit_code;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	exit_code = is_valide_parsing(args, env);
	if (exit_code != -1)
	{
		free(old_path);
		return (exit_code);
	}
	if (!args[1])
		exit_code = ft_cd_no_args(env);
	else if (ft_strcmp(args[1], "-") == 0)
		exit_code = cd_back_pwd(env);
	else
		exit_code = chdir(args[1]);
	if (exit_code == -1)
	{
		perror("cd");
		free(old_path);
		return (1);
	}
	update_env_pwd(&env, old_path);
	return (exit_code);
}
