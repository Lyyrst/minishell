/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:29:47 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:34:36 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Searches for and returns the value of the PATH environment variable.
 *
 * @param env	 The env structure containing the required env var.
 * @return		 The PATH value if found; otherwise, NULL.
 */
char	*find_path_var(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * Builds the full path of a file by concatenating a directory 
 * and a file name.
 *
 * @param dir	The directory in which the file is located.
 * @param cmd	The file name.
 * @return 		The complete path of the file resulting from the concatenation 
 * 				directory and filename.
 */
char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

/**
 * Builds the absolute path of a command by searching the 
 * directories specified in the PATH environment variable.
 *
 * @param cmd	The command whose absolute path is to be built.
 * @param env	The env structure containing the required env var.
 * @return		The absolute path of the command if it is found in 
 * 				one of the directories specified in PATH; otherwise, NULL.
 */
char	*ft_build_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	char	*path_var;
	int		i;

	i = 0;
	path_var = find_path_var(env);
	if (!check_find_path_var(path_var, cmd))
		return (NULL);
	paths = ft_split(path_var, ':');
	while (paths[i])
	{
		path = build_full_path(paths[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_error_no_path(paths, env, cmd);
	return (NULL);
}

void	print_error_path(char	*cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_last_exit_status = 127;
}

/*
** ft_get_path: Finds the executable path of a command.
**
** @param  cmd		  The command to find.
** @param  envp		  Environment variables, including PATH.
** @return			  Full path of the command, or NULL if not found.
**
** Splits PATH, checks each directory for cmd, and returns the path if found.
*/
char	*ft_get_path(t_token *token, t_env *env)
{
	char		*path;

	if (ft_strlen(token->value) == 0 && token->type == UNKNOWN)
		return (NULL);
	if (ft_strlen(token->value) == 0)
	{
		print_error_path("''");
		return (NULL);
	}
	if (ft_is_a_directory(token->value))
		return (NULL);
	if (access(token->value, X_OK) != 0 && ft_strchr(token->value, '/') == NULL)
		path = ft_build_path(token->value, env);
	else
	{
		if (ft_strchr(token->value, '/') == NULL)
		{
			print_error_path(token->value);
			return (NULL);
		}
		path = token->value;
	}
	return (path);
}
