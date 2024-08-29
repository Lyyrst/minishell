/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:20:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 19:23:15 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 1 if str is a valid -n flag and 0 if not a valid -n flag
static int	is_flag_echo(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '-' || ft_strlen(str) <= 1)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// check if there is an flag and return an int to skip it
// return 0 if no flag are valid
static int	skip_flag(char **a)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (a[i] != NULL && is_flag_echo(a[i]) == 1)
	{
		i++;
		ret++;
	}
	return (ret);
}

static int	array_len(char **a)
{
	int	count;

	count = 0;
	if (!a || !a[0])
		return (count);
	while (a[count])
		count++;
	return (count);
}

// execute echo command with args
int	ft_echo(char **args, t_env *env)
{
	int	i;
	int	flag;
	int	len;

	(void)env;
	flag = 0;
	if (args[1])
		flag = skip_flag(args);
	i = flag + 1;
	len = array_len(args);
	while (args[i] && i < len)
	{
		if (args[i][0] != 0)
			ft_putstr_fd(args[i++], 1);
		else
			i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
