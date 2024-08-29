/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 00:00:00 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:41:03 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(int fd)
{
	char	*line;
	char	*tmp;
	char	*buf;
	int		ret;

	buf = malloc(sizeof(char) * 1000 + 1);
	if (!buf)
		return (NULL);
	ret = read(fd, buf, 100);
	if (ret == -1)
		return (NULL);
	buf[ret] = '\0';
	line = ft_strdup(buf);
	while (ft_strchr(line, '\n') == NULL && ret != 0)
	{
		ret = read(fd, buf, 100);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
	}
	free(buf);
	return (line);
}

int	is_valide_lexer(t_token *tokens, char *command)
{
	if (!tokens || !syntaxer(tokens))
	{
		free_tokens(tokens);
		if (command)
			free(command);
		return (0);
	}
	return (1);
}

/**
 * Handles state change when a quote character is encountered
 * in an input string during variable expansion.
 *
 * @param c 				The character currently being processed.
 * @param in_single_quote 	A pointer to the current quote state,
 * 							updated according to character c.
 */
void	handle_quotes(const char c, int *in_single_quote)
{
	if (c == '\'' && *in_single_quote == 0)
		*in_single_quote = 1;
	else if (c == '\'' && *in_single_quote == 1)
		*in_single_quote = 0;
	else if (c == '"' && *in_single_quote == 0)
		*in_single_quote = 2;
	else if (c == '"' && *in_single_quote == 2)
		*in_single_quote = 0;
}

void	get_history(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	(void)argv;
	setup_signal();
	fd = open("config/minishell_history", O_RDONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = 0;
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	add_to_history(char *cmd)
{
	char	*res;
	int		fd;

	res = ft_strjoin(cmd, "\n");
	fd = open("config/minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		free(res);
		return ;
	}
	write(fd, res, ft_strlen(res));
	free(res);
	close(fd);
}
