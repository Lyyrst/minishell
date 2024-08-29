/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:41:26 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/04 16:45:39 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max_long(char **args)
{
	long long	tmp;

	tmp = 0;
	tmp = ft_atoll(args[1]);
	if ((tmp == LLONG_MIN)
		&& (ft_strcmp(args[1], "-9223372036854775808") != 0))
		return (1);
	return (0);
}

void	print_exit_error(char *str, int n)
{
	if (n == 1)
		ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	clear_exit(char **args, t_env *env, t_ast_node *ast, int fd_dup[2])
{
	if (fd_dup[0] != -1)
		close(fd_dup[0]);
	if (fd_dup[1] != -1)
		close(fd_dup[1]);
	ft_free_ast(ast);
	ft_free_tab(args);
	free_env(env);
}

void	check_exit_args(char **args, t_env *env, t_ast_node *ast, int fd_dup[2])
{
	if (!args || !args[1])
	{
		ft_putstr_fd("exit\n", 1);
		clear_exit(args, env, ast, fd_dup);
		exit (g_last_exit_status);
	}
	if (alpha_args(args) || max_long(args))
	{
		print_exit_error(args[1], 1);
		clear_exit(args, env, ast, fd_dup);
		exit (2);
	}
}
