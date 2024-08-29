/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:08:12 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/17 09:08:52 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;
	int	size;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	size = (int)n;
	while (i >= 0 && j >= 0 && size > 0)
	{
		if (s1[i] != s2[j])
			return (1);
		i--;
		j--;
		size--;
	}
	if (s1[i] != s2[j])
		return (1);
	return (0);
}
