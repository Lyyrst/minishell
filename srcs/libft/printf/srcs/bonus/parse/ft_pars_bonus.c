/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:34:31 by bberkrou          #+#    #+#             */
/*   Updated: 2024/02/21 13:29:51 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_flags_conditions(t_flags *flags)
{
	if (*(flags->format_substr) == '-')
		flags->aligne_left = 1;
	else if (*(flags->format_substr) == '0' && flags->aligne_left != 1)
	{
		if (flags->width == 0 && flags->precision == -1)
			flags->zero = 1;
	}
	else if (*(flags->format_substr) == ' ' && flags->space_plus != 1)
		flags->space_plus = -1;
	else if (*(flags->format_substr) == '+')
		flags->space_plus = 1;
	else if (*(flags->format_substr) == '#')
		flags->square = 1;
}

/*
** Dispatches to the appropriate printing function based on the format 
** specifier.
** Handles character, string, pointer, int, unsigned, hex, and percent types.
**
** @param  args      List of arguments to print.
** @param  flags     Struct with flags and specifier information.
** @param  length    Pointer to the accumulator of the total output length.
** @return           None. Modifies length through specific print functions.
*/
void	ft_hub(va_list args, t_flags flags, int *lenght)
{
	if (flags.param == 'c')
		ft_print_char(args, flags, lenght);
	else if (flags.param == 's')
		ft_print_string(args, flags, lenght);
	else if (flags.param == 'p')
		ft_print_pointer(args, flags, lenght);
	else if (flags.param == 'd' || flags.param == 'i')
		ft_print_int(args, flags, lenght);
	else if (flags.param == 'u')
		ft_print_unsigned_int(args, flags, lenght);
	else if (flags.param == 'x' || flags.param == 'X')
		ft_print_hexa(args, flags, lenght);
	else if (flags.param == '%')
		ft_print_percent(args, flags, lenght);
}

void	ft_process_manage_flags(t_flags *flags)
{
	int	num;

	num = ft_atoi(flags->format_substr);
	flags->width = num;
	while (ft_isdigit(*flags->format_substr))
		flags->format_substr++;
	flags->format_substr--;
}

/*
** Manages and processes formatting flags from a format substring.
** Determines precision and width, and delegates to specific handlers.
**
** @param  args      List of arguments for the format specifiers.
** @param  flags     Struct containing flag information and substrings.
** @param  length    Pointer to the total output length accumulator.
** @return           None. Modifies length and flags indirectly.
*/
void	ft_manage_flags(va_list args, t_flags flags, int *lenght)
{
	while (!is_determiner(*flags.format_substr))
	{
		if (ft_isdigit(*flags.format_substr) && *flags.format_substr != '0')
			ft_process_manage_flags(&flags);
		else if (*flags.format_substr == '.')
		{
			if (ft_isdigit(*(flags.format_substr + 1)))
			{
				flags.precision = ft_atoi(flags.format_substr + 1);
				while (ft_isdigit(*(flags.format_substr + 1)))
					flags.format_substr++;
			}
			else
				flags.precision = 0;
		}
		else
			ft_flags_conditions(&flags);
		flags.format_substr++;
	}
	flags.param = *flags.format_substr;
	ft_hub(args, flags, lenght);
}

/*
** Parses the format string for conversion specifications, processes them,
** and outputs the formatted result. Supports custom flag processing.
**
** @param  format    The format string to parse.
** @param  args      List of arguments for format specifiers.
** @param  length    Pointer to total output length accumulator.
** @return           None. Modifies the length indirectly.
*/
void	ft_pars_format(const char *format, va_list args, int *lenght)
{
	int	i;

	while (*format)
	{
		i = 0;
		if (*format == '%')
		{
			format++;
			while (is_flag(*format) && !is_determiner(*format))
			{
				i++;
				format++;
			}
			ft_isolate_flags((format - i), i + 1, args, lenght);
		}
		else
			*lenght += write(1, format, 1);
		format++;
	}
}
