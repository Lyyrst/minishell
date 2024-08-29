/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:02:29 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:12:16 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_envvar_here_doc(const char *input, t_env *env)
{
	char				*result;
	int					i;
	int					j;
	int					in_single_quote;
	t_expansion_params	params;

	result = malloc(sizeof(char) * 1);
	result[0] = 0;
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	params.result = &result;
	params.i = &i;
	params.j = &j;
	params.in_single_quote = &in_single_quote;
	while (input[i])
		handle_variable_expansion(input, &params, env);
	return (result);
}

static void	expend_var(char *line, int fd, int fd_new, t_env *env)
{
	char	*line_expend;

	while (line)
	{
		line_expend = ft_expand_envvar_here_doc(line, env);
		write (fd_new, line_expend, ft_strlen(line_expend));
		free(line);
		free(line_expend);
		line = get_next_line(fd);
	}
}

char	*xp_heredoc(char *filename, t_env *env)
{
	int		fd;
	int		fd_new;
	char	*new_filename;
	char	*line;

	new_filename = temp_filename();
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	free(filename);
	fd_new = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_new == -1)
		return (NULL);
	line = get_next_line(fd);
	expend_var(line, fd, fd_new, env);
	close(fd);
	close(fd_new);
	return (new_filename);
}
