/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:14:35 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 02:07:05 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get the arguments from a token list.
 *
 * @param token The token list.
 * @return The array of arguments.
 * @note Expend wilercard
 */
char	**get_args(t_token *token)
{
	char	**args;
	int		i;
	t_token	*cursor;

	if (!token)
		return (NULL);
	if (!replace_wilercard(&token))
		return (NULL);
	cursor = token;
	i = get_args_number(cursor);
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	cursor = token;
	while (cursor)
	{
		if (cursor->type != WILERCARD)
			args[i++] = ft_strdup(cursor->value);
		cursor = cursor->next;
	}
	args[i] = NULL;
	return (args);
}

static void	close_dup(int save_fd, int save_fd1)
{
	dup2(save_fd, STDOUT_FILENO);
	close(save_fd);
	dup2(save_fd1, STDIN_FILENO);
	close(save_fd1);
}

void	exec_builtins_no_fork(int pipe_fds[2], t_ast_node *root, t_env **env)
{
	int		save_fd;
	int		save_fd_1;
	int		save_exit_status;
	int		fd_dup[2];

	save_exit_status = g_last_exit_status;
	save_fd = dup(STDOUT_FILENO);
	save_fd_1 = dup(STDIN_FILENO);
	fd_dup[0] = save_fd;
	fd_dup[1] = save_fd_1;
	process_exec_fd(STDIN_FILENO, pipe_fds, root, *env);
	if (g_last_exit_status != 0)
	{
		close_dup(save_fd, save_fd_1);
		return ;
	}
	g_last_exit_status = save_exit_status;
	g_last_exit_status = exec_builtins(root->token, env, root, fd_dup);
	close_dup(save_fd, save_fd_1);
	return ;
}

void	process_exec_fd_dup(int in_fd, int pipe_fds[2])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (pipe_fds[1] != STDOUT_FILENO)
	{
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	if (pipe_fds[0] > 2)
		close(pipe_fds[0]);
}

void	process_exec_cmd_builtins(t_ast_node *root, t_env *env, int fd_dup[2])
{
	int	exit_builtins;

	exit_builtins = exec_builtins(root->token, &env, root, fd_dup);
	free_env(env);
	if (root->here_doc)
		ft_free_redirection(*(root->here_doc));
	ft_free_ast(root);
	exit(exit_builtins);
}
