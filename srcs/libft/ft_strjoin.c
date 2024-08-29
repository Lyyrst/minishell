/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:39:26 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/28 14:27:24 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)s1, size);
	ft_strlcat(res, (char *)s2, size);
	return (res);
}

char	*ft_strjoin_free(char *residual, char *buff)
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
