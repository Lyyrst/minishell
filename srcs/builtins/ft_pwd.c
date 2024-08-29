/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:27:42 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 17:51:50 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pars_args(char **argv)
{
	if (!argv || !*argv)
		return (0);
	while (*argv)
	{
		if (*argv[0] == '-')
		{
			ft_putstr_fd("env: invalid option -- '", 2);
			ft_putchar_fd(argv[0][0], 2);
			ft_putchar_fd(argv[0][1], 2);
			argv++;
			ft_putstr_fd("'\nTry 'pwd --help' for more information.\n", 2);
			return (125);
		}
		argv++;
	}
	return (0);
}

int	ft_pwd(char **args, t_env *env)
{
	char	*path;
	int		exit_status;

	if (!env)
	{
		perror("Error NULL");
		return (1);
	}
	if (args)
		args++;
	exit_status = pars_args(args);
	if (exit_status != 0)
		return (exit_status);
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("Error\n");
		return (1);
	}
	ft_printf("%s\n", path);
	free(path);
	return (0);
}
