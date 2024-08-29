/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:00:32 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 17:24:45 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here_doc	*init_data(char **delimiter, char *filename, \
						t_token *token, t_redirection *here_doc)
{
	t_here_doc	*data;

	data = malloc(sizeof(t_here_doc));
	if (!data)
		return (NULL);
	data->delimiter = delimiter;
	data->filename = filename;
	data->token = token;
	data->here_doc = here_doc;
	return (data);
}

void	free_fork_here_doc(t_here_doc *data, t_env *env)
{
	free(data->filename);
	data->filename = NULL;
	free(*(data->delimiter));
	*(data->delimiter) = NULL;
	free_tokens(data->token);
	data->token = NULL;
	ft_free_redirection(data->here_doc);
	data->here_doc = NULL;
	free_env(env);
	free(data);
}

t_redirection_type	get_type_here_doc(t_token_type type)
{
	if (type == DELIMITER_NO_EXPEND)
		return (T_HEREDOC_NO_EXPEND);
	else
		return (T_HEREDOC);
}
