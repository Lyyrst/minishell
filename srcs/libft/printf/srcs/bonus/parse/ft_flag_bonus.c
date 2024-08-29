/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:13:30 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 10:40:10 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_flag(char c)
{
	return (ft_strchr("0# +-123456789.", c) != NULL);
}

int	is_determiner(char c)
{
	return (ft_strchr("cspdiuxX%", c) != NULL);
}

void	ft_numbers_in_flags(t_flags *flags)
{
	if (*(flags->format_substr) == '.')
	{
		flags->format_substr++;
		if (ft_isdigit(*(flags->format_substr)) == 1)
			flags->precision = ft_atoi(flags->format_substr);
		else if (ft_isdigit(*(flags->format_substr) == 0))
			flags->precision = 0;
	}
	else
	{
		if (ft_isdigit(*(flags->format_substr)) == 1)
			flags->width = ft_atoi(flags->format_substr);
	}
}
