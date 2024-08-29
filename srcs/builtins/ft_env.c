/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 05:46:01 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 21:24:39 by kbutor-b         ###   ########.fr       */
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
			ft_putstr_fd(*argv++, 2);
			ft_putstr_fd("\nTry 'env --help' for more information.\n", 2);
			return (125);
		}
		else
		{
			ft_putstr_fd("env: ‘", 2);
			ft_putstr_fd(*argv++, 2);
			ft_putstr_fd("’: No such file or directory\n", 2);
			return (127);
		}
	}
	return (0);
}

int	ft_env(char **argv, t_env *env)
{
	int	exit_status;

	if (argv)
		argv++;
	exit_status = pars_args(argv);
	if (exit_status != 0)
		return (exit_status);
	while (env)
	{
		if (env->print == 1)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
