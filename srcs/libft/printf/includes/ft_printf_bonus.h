/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:23:57 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/20 11:15:45 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "../../libft.h"
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flags
{
	int		width;
	int		precision;
	int		zero;
	int		aligne_left;
	int		space_plus;
	char	param;
	char	*format_substr;
	char	*format_str;
	int		square;
}			t_flags;

typedef struct s_display_info
{
	t_flags		flags;
	int			*length;
	int			str_len;
	long int	number;
	char		*str;
}				t_display_info;

typedef struct s_uint_info
{
	t_flags			flags;
	int				*length;
	int				str_len;
	unsigned int	number;
	char			*str;
}				t_uint_info;

void	ft_pars_format(const char *format, va_list args, int *lenght);
int		is_flag(char c);
int		is_determiner(char c);
void	ft_numbers_in_flags(t_flags *flags);
int		ft_printf(const char *format, ...);

void	ft_print_int(va_list args, t_flags flags, int *lenght);
void	ft_print_unsigned_int(va_list args, t_flags flags, int *length);
void	ft_print_percent(va_list args, t_flags flags, int *length);
void	ft_print_hexa(va_list args, t_flags flags, int *length);
void	ft_print_pointer(va_list args, t_flags flags, int *length);
void	ft_print_char(va_list args, t_flags flags, int *length);

void	print_flag(t_flags flags);
void	print_width(int width, int *length);
void	print_zero(int width, int *length);
void	print_padding(int number, int width, int *length, t_flags flags);
int		print_sign(int number, int *length, t_flags flags);
void	ft_print_string(va_list args, t_flags flags, int *length);

size_t	ft_count_digits(unsigned int n);
char	*ft_utoa(unsigned int n);
char	*ft_uitoa_base(unsigned long long n, char *base);
void	ft_init_flag(char *str, va_list args, int *lenght);
void	ft_isolate_flags(const char *format, int len, \
							va_list args, int *lenght);
void	ft_manage_flags(va_list args, t_flags flags, int *lenght);

#endif
