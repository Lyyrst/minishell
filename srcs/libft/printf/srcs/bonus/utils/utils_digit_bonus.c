/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_digit_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:30:22 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:31 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

size_t	ft_count_digits(unsigned int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_utoa(unsigned int n)
{
	size_t	len;
	char	*str;

	len = ft_count_digits(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		while (len > 0)
		{
			len--;
			str[len] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}

int	get_num_len(unsigned long long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		len = 1;
	else
	{
		while (num != 0)
		{
			num /= base;
			len++;
		}
	}
	return (len);
}

char	*ft_uitoa_base(unsigned long long n, char *base)
{
	int		base_len;
	int		num_len;
	char	*str;

	base_len = ft_strlen(base);
	num_len = get_num_len(n, base_len);
	str = (char *)malloc((num_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[num_len] = '\0';
	while (num_len--)
	{
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
