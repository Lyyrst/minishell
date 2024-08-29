/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 01:56:42 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:51:50 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_is_directory(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_last_exit_status = 126;
}

void	*no_such_file(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_last_exit_status = 127;
	return (NULL);
}

int	check_find_path_var(char *path_var, char *cmd)
{
	char	**paths;

	if (!path_var)
	{
		no_such_file(cmd);
		return (0);
	}
	paths = ft_split(path_var, ':');
	if (paths[0] == 0)
	{
		ft_free_tab(paths);
		no_such_file(cmd);
		return (0);
	}
	ft_free_tab(paths);
	return (1);
}

int	ft_is_a_directory(char *cmd)
{
	struct stat	*s;

	if (ft_strchr(cmd, '/') == NULL)
		return (0);
	s = malloc(sizeof(struct stat));
	if (!s)
		return (0);
	if (stat(cmd, s) == -1)
	{
		perror(cmd);
		if (errno == EACCES)
			g_last_exit_status = 126;
		else
			g_last_exit_status = 127;
		free(s);
		return (1);
	}
	if (S_ISDIR(s->st_mode))
	{
		print_error_is_directory(cmd);
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

void	ft_error_no_path(char **paths, t_env *env, char *cmd)
{
	char	*tmp;

	ft_free_tab(paths);
	ft_putstr_fd(cmd, 2);
	tmp = get_var_value("PATH", env);
	if (ft_strncmp(tmp, "\0", 1) == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	free(tmp);
	g_last_exit_status = 127;
}
