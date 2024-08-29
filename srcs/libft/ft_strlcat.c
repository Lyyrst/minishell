/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:03:52 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/24 16:33:07 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *str, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		i++;
	return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	length;

	if (size == 0)
		return (ft_strlen(src));
	length = ft_strnlen(dest, size);
	if (length == size)
		return (length + ft_strlen(src));
	return (length + ft_strlcpy(dest + length, src, size - length));
}
