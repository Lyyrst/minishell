/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:25:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:36:44 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Executes a pipeline command represented by an AST node.
 *
 * @param data 		A pointer to the struc `t_pipe` containing the data 
 * 					required to execute the pipeline command.
 * @param pipe_fds 	An array of file descriptors for * communication via a pipe.
 * 					communication via a pipe.
 * @param err_code 	A pointer to the error code of the * command execution. 
 * 					command execution.
 */
void	pipe_exec_pipe(t_pipe *d, int pipe_fds[2], int *err_code)
{
	int			pid;

	pipe(pipe_fds);
	pid = exec_command(d->node->left, d->fd_in, pipe_fds, d->env);
	close(pipe_fds[1]);
	if (d->fd_in > 2)
		close(d->fd_in);
	exec_pipeline(d->node->right, d->env, pipe_fds[0]);
	waitpid(pid, err_code, 0);
}

/**
 * Executes a simple command represented by an AST node.
 *
 * @param data 		A pointer to the `t_pipe` structure
 * @param pipe_fds 	An array of file descriptors for
 * 					communication via a pipe.
 * @param err_code 	A pointer to the error code of the * command execution. 
 * 					command execution. 
 */
void	pipe_exec_cmd(t_pipe *d, int pipe_fds[2], int *err_code)
{
	int		pid;

	pipe_fds[0] = -1;
	pipe_fds[1] = STDOUT_FILENO;
	pid = exec_command(d->node, d->fd_in, pipe_fds, d->env);
	if (d->fd_in > 2)
		close(d->fd_in);
	if (pid > 0)
	{
		waitpid(pid, err_code, 0);
		if (WIFEXITED(*err_code))
			g_last_exit_status = WEXITSTATUS(*err_code);
		if (WIFSIGNALED(*err_code))
		{
			g_last_exit_status = WTERMSIG(*err_code);
			if (g_last_exit_status != 131)
				g_last_exit_status += 128;
			if (g_last_exit_status == 131)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
}

/**
 * Executes a pipeline represented by an AST node.
 *
 * @param node 	The AST node representing the pipeline to be executed.
 * @param env	A pointer to the env structure containing the env var.
 * @param fd_in The input file descriptor for the pipeline.
 * @note 		This function calls either `pipe_exec_pipe` if the node 
 * 				node represents a pipeline, or `pipe_exec_cmd` if the
 * 				node represents a simple command.
 */
void	exec_pipeline(t_ast_node *node, t_env *env, int fd_in)
{
	int		pipe_fds[2];
	int		err_code;
	t_pipe	data;

	if (node == NULL)
		return ;
	data.node = node;
	data.env = env;
	data.fd_in = fd_in;
	signal(SIGINT, process_sigint_muted);
	signal(SIGQUIT, process_sigquit);
	if (node->type == PIPE)
		pipe_exec_pipe(&data, pipe_fds, &err_code);
	else
		pipe_exec_cmd(&data, pipe_fds, &err_code);
}
