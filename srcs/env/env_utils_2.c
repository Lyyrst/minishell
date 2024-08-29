/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:53:15 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 00:59:23 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_var_if_first(char *key, t_env **env)
{
	t_env	*tmp;

	if (ft_strcmp(key, (*env)->key) == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (1);
	}
	return (0);
}
