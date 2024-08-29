/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:55:29 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 19:29:31 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_env **env)
{
	if (!args || !*args || !env)
		return (0);
	args++;
	while (*args)
	{
		if (search_var_in_env(*args, *env))
			remove_var_in_env(*args, env);
		args++;
	}
	return (0);
}
