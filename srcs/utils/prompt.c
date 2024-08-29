/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:28:39 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:40:36 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_host(void)
{
	char	*line;
	char	**tab;
	char	*host;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = gnl(fd);
	close(fd);
	if (!line)
		return (NULL);
	tab = ft_split(line, '.');
	free(line);
	if (!tab)
		return (NULL);
	host = ft_strdup(tab[0]);
	ft_free_tab(tab);
	return (host);
}

char	*process_get_path_prompt(char *pwd, char *home)
{
	char	*path;

	path = malloc(sizeof(char) * (ft_strlen(pwd) - ft_strlen(home) + 2));
	if (!path)
	{
		free(pwd);
		free(home);
		return (NULL);
	}
	if (home && ft_strlen(home) != 0)
		path[0] = '~';
	else
		path[0] = ':';
	ft_strcpy(path + 1, pwd + ft_strlen(home));
	return (path);
}

char	*get_path_prompt(t_env *env)
{
	char	*pwd;
	char	*home;
	char	*path;

	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	if (!pwd || !home)
		return (NULL);
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		if (strlen(pwd) == ft_strlen(home))
			path = ft_strdup("~");
		else
		{
			path = process_get_path_prompt(pwd, home);
		}
	}
	else
		path = ft_strdup(pwd);
	free(pwd);
	free(home);
	return (path);
}

void	assembly_prompt(char **prompt, char *user, char *host, char *path)
{
	strcpy(*prompt, user);
	strcat(*prompt, "@");
	strcat(*prompt, host);
	strcat(*prompt, path);
	strcat(*prompt, "$ ");
	free(user);
	free(host);
	free(path);
}

/**
 * Builds the shell command prompt by combining the username,
 * hostname and the current path of the working directory.
 *
 * @param env 	The pointer to the environment structure.
 * @return		A pointer to the string containing the command prompt. 
 * 				command prompt. NULL in case of error 
 * 				or insufficient memory allocation.
 */
char	*build_prompt(t_env *env)
{
	char	*prompt;
	char	*user;
	char	*host;
	char	*path;

	path = get_path_prompt(env);
	user = ft_getenv("USER", env);
	host = get_host();
	prompt = malloc(sizeof(char) * (ft_strlen(user) + ft_strlen(host) \
													+ ft_strlen(path) + 3 + 1));
	if (!prompt)
	{
		free(user);
		free(host);
		free(path);
		return (NULL);
	}
	assembly_prompt(&prompt, user, host, path);
	return (prompt);
}
