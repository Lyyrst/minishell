/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilercard_filtre_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:08:50 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 14:54:47 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	patern1(char *d_name, char *filtre, int *i, int *j)
{
	while (filtre[*j] && d_name[*i] && filtre[*j] != '*')
	{
		if (filtre[*j] != d_name[*i])
			return (0);
		(*i)++;
		(*j)++;
	}
	if ((!d_name[*i] && filtre[*j] != '*'))
		return (0);
	if ((!d_name[*i] && filtre[*j]))
		return (0);
	return (1);
}

int	patern2(char *d_name, char *filtre, int *i, int *j)
{
	while (filtre[(*j)] && filtre[(*j)] == '*')
		(*j)++;
	if (!filtre[(*j)])
		return (1);
	while (d_name[(*i)] && d_name[(*i)] != filtre[(*j)])
		(*i)++;
	if (d_name[(*i)] == 0)
		return (0);
	if (!filtre[(*j)])
		return (1);
	(*i)++;
	(*j)++;
	return (2);
}

int	patern3(char *d_name, char *filtre)
{
	int	i;
	int	j;

	i = ft_strlen(d_name);
	j = ft_strlen(filtre);
	while (i >= 0 && j >= 0 && filtre[j] != '*')
	{
		if (d_name[i] != filtre[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

/**
 * Check if a file name matches a wildcard filter.
 *
 * @param d_name The file name.
 * @param filtre The wildcard filter.
 * @return 1 if the file name matches the filter, otherwise 0.
 */
int	is_valide_filtre(char *d_name, char *filtre)
{
	int		i;
	int		j;
	int		status;

	i = 0;
	j = 0;
	while (filtre[j] && d_name[i])
	{
		if (filtre[j] != '*')
		{
			if (!patern1(d_name, filtre, &i, &j))
				return (0);
		}
		else if (filtre[j] == '*')
		{
			status = patern2(d_name, filtre, &i, &j);
			if (status == 0 || status == 1)
				return (status);
		}
		if (ft_strchr(&(filtre[j]), '*') == NULL)
			return (patern3(d_name, filtre));
	}
	return (1);
}
