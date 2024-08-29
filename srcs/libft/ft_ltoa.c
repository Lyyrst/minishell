/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:21:47 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 08:22:29 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_ltoa(long n)
{
	char	*str;
	int		len;
	long	nbr;
	int		is_negative;

	if (n < 0)
		is_negative = 1;
	else
		is_negative = 0;
	len = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	nbr = n;
	if (is_negative)
		nbr = -nbr;
	while (len-- > 0)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}
