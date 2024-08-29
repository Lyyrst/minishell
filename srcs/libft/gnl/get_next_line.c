/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:51:41 by bberkrou          #+#    #+#             */
/*   Updated: 2023/11/06 05:13:07 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** Extracts a line from the given string up to a newline character
** or to the end of the string if no newline is found.
**
** @param  source   The string from which the line is extracted.
** @return            The extracted line or NULL if the string is empty.
*/
char	*extract_line(char *source)
{
	char	*cursor;
	char	*line;
	char	*line_start;

	if (!*source)
		return (NULL);
	cursor = source;
	while (*cursor && *cursor != '\n')
		cursor++;
	line = malloc(sizeof(char) * (cursor - source + 2));
	if (!line)
		return (NULL);
	line_start = line;
	while (*source && *source != '\n')
		*line++ = *source++;
	if (*source == '\n')
		*line++ = *source;
	*line = '\0';
	return (line_start);
}

/*
** Creates a new string after the newline character found in 'residual',
** effectively removing the extracted line from the original string.
**
** @param  source   The original string containing the extracted line.
** @return            A new string that starts after the newline character
**                    or NULL if no newline is found.
*/
char	*new_residual(char *source)
{
	char	*cursor;
	char	*new_str;
	char	*new_str_start;

	cursor = source;
	while (*cursor && *cursor != '\n')
		cursor++;
	if (!*cursor)
	{
		free(source);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(cursor) + 1));
	if (!new_str)
		return (NULL);
	new_str_start = new_str;
	cursor++;
	while (*cursor)
		*new_str++ = *cursor++;
	*new_str = '\0';
	free(source);
	return (new_str_start);
}

/*
** Reads characters from file descriptor into the buffer until newline
** is found or the end of file is reached. Joins the buffer content
** to the static resover string from previous calls.
**
** @param  fd         The file descriptor to read from.
** @param  residual   The static string containing resovers from previous reads.
** @return            The updated string containing read characters including
**                    the newline character if it was found.
*/
char	*read_to_residual(int fd, char *residual)
{
	char	*buff;
	char	*new_residual;
	int		rd_bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	new_residual = residual;
	while (!ft_strchr_gnl(new_residual, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		new_residual = ft_strjoin_gnl(new_residual, buff);
	}
	free(buff);
	return (new_residual);
}

/*
** Retrieves the next line from the file descriptor specified.
** A line is defined as a sequence of characters followed by a '\n' or EOF.
**
** @param  fd   The file descriptor to read from.
** @return      A string containing the next line from the file descriptor.
*/
char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*residual;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	residual = read_to_residual(fd, residual);
	if (!residual)
		return (NULL);
	current_line = extract_line(residual);
	residual = new_residual(residual);
	return (current_line);
}
