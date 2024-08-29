/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:08:24 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/30 15:57:37 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *residual, char *buff)
{
	char	*str;
	char	*str_start;
	char	*residual_start;

	if (!residual)
	{
		residual = (char *)malloc(1 * sizeof(char));
		residual[0] = '\0';
	}
	if (!residual || !buff)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(residual) + ft_strlen(buff) + 1));
	if (str == NULL)
		return (NULL);
	str_start = str;
	residual_start = residual;
	while (*residual)
		*str++ = *residual++;
	while (*buff)
		*str++ = *buff++;
	*str = '\0';
	free(residual_start);
	return (str_start);
}
