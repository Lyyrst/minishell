/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:38:49 by bberkrou          #+#    #+#             */
/*   Updated: 2023/11/06 05:14:52 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*read_to_residual(int fd, char *residual);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *residual, char *buff);
char	*extract_line(char *source);
char	*new_residual(char *source);

#endif
