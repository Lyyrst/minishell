/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:59:30 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:35:33 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection_type	ft_type_to_redirection(t_token_type token)
{
	t_redirection_type	type;

	if (token == REDIRECT_IN)
		type = T_REDIRECT_IN;
	else if (token == REDIRECT_OUT)
		type = T_REDIRECT_OUT;
	else if (token == HERE_DOC)
		type = T_HEREDOC;
	else if (token == REDIRECT_APPEND)
		type = T_APPEND;
	else
		type = T_REDIRECT_NONE;
	return (type);
}

/**
 * Replaces each T_HEREDOC redirect with a T_REDIRECT_IN redirect. 
 * T_REDIRECT_IN input redirection.
 *
 * @param redirections	 The list of redirections to be processed.
 */
void	replace_heredocs_with_infiles(t_redirection *redirections)
{
	t_redirection	*current;

	current = redirections;
	while (current)
	{
		if (current->type == T_HEREDOC)
			current->type = T_REDIRECT_IN;
		current = current->next;
	}
}

/**
 * Opens the file specified in the redirection and returns its fd.
 *
 * @param 	redirections The redirection to be processed.
 * @return 	The fd of the opened file, or -1 in case of error.
 */
int	get_fd(t_redirection *redirections)
{
	int	fd;

	if (redirections->type == T_REDIRECT_OUT)
		fd = open(redirections->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirections->type == T_APPEND)
		fd = open(redirections->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirections->type == T_REDIRECT_IN)
		fd = open(redirections->filename, O_RDONLY);
	else
		fd = -1;
	return (fd);
}

/**
 * Configures the fd redirects specified in the redirect list.
 *
 * @param redirections 	The list of redirections to be configured.
 * @return 				0 if redirections are successfully configured, 
 * 						1 in case of error.
 */
int	setup_redirections(t_redirection *redirections)
{
	int	fd;

	replace_heredocs_with_infiles(redirections);
	while (redirections)
	{
		fd = get_fd(redirections);
		if (fd == -1)
		{
			perror(redirections->filename);
			return (1);
		}
		if (redirections->type == T_REDIRECT_OUT
			|| redirections->type == T_APPEND)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirections->type == T_REDIRECT_IN)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redirections = redirections->next;
	}
	return (0);
}
