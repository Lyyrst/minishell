/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 06:45:36 by bberkrou          #+#    #+#             */
/*   Updated: 2024/05/02 09:47:40 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//modified ft_atoll to look if the str is bigger than the long long value
long long	ft_atoll(const char *str)
{
	int			i;
	long long	ret;
	int			sign;

	i = 0;
	ret = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ret > LLONG_MAX / 10 || (ret == LLONG_MAX / 10
				&& str[i] - '0' > LLONG_MAX % 10))
			return (LLONG_MIN);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}

static int	array_len(char **a)
{
	int	count;

	count = 0;
	if (!a || !*a)
		return (count);
	while (a[count])
		count++;
	return (count);
}

int	alpha_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i][j] == ' ' || (args[i][j] >= 9 && args[i][j] <= 13))
		j++;
	if (args[i][j] == '-' || args[i][j] == '+')
		j++;
	while (args[i][j])
	{
		if (ft_isalpha(args[i][j]) || args[i][j] == '+' \
			|| args[i][j] == '-' || args[i][j] == ' ' \
			|| (args[i][j] >= 9 && args[i][j] <= 13))
			return (1);
		j++;
	}
	return (0);
}

static int	get_exit_code(char **args)
{
	long long	code;

	code = ft_atoll(args[1]);
	if ((code == LLONG_MIN)
		&& (ft_strcmp(args[1], "-9223372036854775808") != 0))
	{
		ft_putstr_fd("exit\n", 1);
		print_exit_error(args[1], 0);
		return (2);
	}
	ft_putstr_fd("exit\n", 1);
	if (code > 255)
		return (code % 256);
	return (code);
}

// return exit code properly between 0 - 255, and modulo 256 if exit code > 255
// if exit code isn't in long long range, exit and return 2
// (echo $? return 2 if the value passed to exit is bigger than long long)
// if more than 1 arguments, return -1 and dont exit
int	ft_exit(char **args, t_env *env, t_ast_node *ast, int fd_dup[2])
{
	int			len;
	long long	code;

	len = array_len(args);
	code = 0;
	if (!env)
		return (-1);
	check_exit_args(args, env, ast, fd_dup);
	if (len > 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	if (len == 2)
		code = get_exit_code(args);
	clear_exit(args, env, ast, fd_dup);
	exit (code);
	return (-1);
}
