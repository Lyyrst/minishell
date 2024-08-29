/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:03:19 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:19:46 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Manages fd redirection before command execution.
 *
 * @param in_fd 	The input fd for the command.
 * @param pipe_fds 	The array containing the pipeline fd.
 * @param node 		The AST node representing the command to be executed.
 * @param env 		The environment structure containing the environment var.
 */
void	process_exec_fd(int in_fd, int pipe_fds[2], \
							t_ast_node *node, t_env *env)
{
	int	status_fd;

	process_exec_fd_dup(in_fd, pipe_fds);
	status_fd = setup_redirections(node->redirections);
	if (!node->token || status_fd == 1)
	{
		if (pipe_fds[0] != -2)
		{
			free_env(env);
			if (node->here_doc)
				ft_free_redirection(*(node->here_doc));
			ft_free_ast(node);
			exit(status_fd);
		}
		else
			g_last_exit_status = status_fd;
	}
	g_last_exit_status = status_fd;
}

/**
 * retrieves the absolute path of the command to be executed from env.
 *
 * @param node 	The AST node representing the command to be executed.
 * @param env 	The environment structure containing the env var.
 * @return 		The absolute path of the command if found in the env, 
 * 				or exec_commn NULL.
 */
char	*process_exec_path(t_ast_node *node, t_env *env)
{
	char	*path;

	path = ft_get_path(node->token, env);
	if (!path)
	{
		free_env(env);
		if (node->here_doc)
			ft_free_redirection(*(node->here_doc));
		ft_free_ast(node);
		exit(g_last_exit_status);
	}
	return (path);
}

/**
 * Executes the command specified by the AST node using execve.
 *
 * @param node 	The AST node representing the command to be executed.
 * @param env 	The env structure containing env variables.
 */
void	process_exec_cmd(t_ast_node *node, t_env *env)
{
	char	*path;
	char	**args;
	char	**envp;

	while (node->token && (ft_strlen(node->token->value) == 0 \
			&& node->token->type == UNKNOWN) && node->token->next)
		node->token = node->token->next;
	path = process_exec_path(node, env);
	args = get_args(node->token);
	envp = ft_env_to_array(env);
	if (execve(path, args, envp) == -1)
	{
		perror(path);
		free_env(env);
		free(path);
		ft_free_tab(envp);
		ft_free_tab(args);
		if (node->here_doc)
			ft_free_redirection(*(node->here_doc));
		ft_free_ast(node);
		exit(126);
	}
}

/**
 * Executes an external command represented by an AST 
 * in a child process.
 *
 * @param root 		The AST node representing the command to be executed.
 * @param in_fd 	The input file descriptor for the command.
 * @param pipe_fds 	An array of file descriptors for 
 * 					communication via a pipe.
 * @param env 		A pointer to the environment structure.
 * @return 			The PID of the child process, or -1 on error.
 */
int	exec_command(t_ast_node *root, int in_fd, int *pipe_fds, t_env *env)
{
	pid_t		pid;
	int			fd_dup[2];

	fd_dup[0] = -1;
	fd_dup[1] = -1;
	signal(SIGINT, process_sigint);
	pid = fork();
	if (pid == 0)
	{
		process_exec_fd(in_fd, pipe_fds, root, env);
		if (is_builtins(root->token))
			process_exec_cmd_builtins(root, env, fd_dup);
		process_exec_cmd(root, env);
		free_env(env);
		if (root->here_doc)
			ft_free_redirection(*(root->here_doc));
		ft_free_ast(root);
	}
	return (pid);
}

/**
 * Executes an abstract syntax tree (AST) representing a command.
 *
 * @param root 	The root node of the AST to be executed.
 * @param env 	A pointer to the env structure containing env var.
 * @note 		This function pre-processes here-documents, 
 * 				then executes the pipeline from the root node.
 */
void	execute_ast(t_ast_node *root, t_env **env)
{
	int		pipe_fds[2];

	signal(SIGINT, process_sigint);
	if (pre_process_heredocs(&root, *env))
		return ;
	pipe_fds[0] = -2;
	pipe_fds[1] = STDOUT_FILENO;
	if (root && root->token && is_builtins(root->token))
	{
		exec_builtins_no_fork(pipe_fds, root, env);
		return ;
	}
	exec_pipeline(root, *env, STDIN_FILENO);
}
