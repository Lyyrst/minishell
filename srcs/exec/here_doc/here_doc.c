/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:51:09 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:30:56 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Writes here-document contents to a given fd file.
 *
 * @param delimiter The here-document delimiter.
 * @param env 		The env structure containing the required env var.
 * @param fd 		The fd where to write the contents of the here-document.
 */
void	write_heredoc(char *delimiter, t_env *env, int fd)
{
	char	*line;

	if (g_last_exit_status == -2147483648)
		return ;
	line = readline("> ");
	if (!line && g_last_exit_status != -2147483648)
		print_error_heredoc(delimiter);
	process_write_heredoc(line, delimiter, fd, env);
}

/**
 * Create a child process to manage a here-document.
 *
 * @param filename	The name of the temporary file to store 
 * 					the contents of the here-document.
 * @param delimiter The here-document delimiter.
 * @param env 		The env structure containing the necessary env var.
 * @param root 		The root node of the abstract syntax tree (AST).
 * @return 			The PID of the child process, or -1 on error.
 */
int	fork_heredoc(t_here_doc *data, t_env *env)
{
	int		pid;
	int		fd;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, process_sigint_heredoc);
		fd = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error: Failed to create temporary file for heredoc");
			exit(EXIT_FAILURE);
		}
		write_heredoc(*(data->delimiter), env, fd);
		free_fork_here_doc(data, env);
		close(fd);
		if (g_last_exit_status == -2147483648)
			exit(130);
		(void)fd;
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

/**
 * Processes here-documents in a node of the abstract syntax tree (AST).
 *
 * @param node 	The AST node containing the redirections to be processed.
 * @param env 	The env structure containing the env var.
 * @param root 	The root node of the abstract syntax tree (AST).
 * @return 		1 if an error has occurred while processing 
 * 				here-documents, otherwise 0.
 */
int	handle_heredoc(t_here_doc *data, t_env *env)
{
	int		tmp_fd;
	int		pid;
	int		err_code;

	pid = fork_heredoc(data, env);
	waitpid(pid, &err_code, 0);
	signal(SIGINT, process_sigint);
	if (err_code != 0)
	{
		g_last_exit_status = 130;
		return (-1);
	}
	tmp_fd = open(data->filename, O_RDONLY);
	if (tmp_fd == -1)
	{
		perror("Error: Failed to open temporary file for heredoc");
		exit(EXIT_FAILURE);
	}
	return (tmp_fd);
}

/**
 * Processes here-documents in a node of the abstract syntax tree (AST).
 *
 * @param node 	The AST node containing the redirections to be processed.
 * @param env	The env structure containing the env var.
 * @param root 	The root node of the abstract syntax tree (AST).
 * @return		1 if an error has occurred while processing 
 * 				here-documents, otherwise 0.
 */
int	process_heredocs(t_ast_node **node, t_env *env)
{
	t_redirection	*curr;

	(void)env;
	curr = (*node)->redirections;
	while (curr)
	{
		if (curr->type == T_HEREDOC || curr->type == T_HEREDOC_NO_EXPEND)
		{
			free(curr->filename);
			if ((*(*node)->here_doc)->type == T_HEREDOC_NO_EXPEND)
				curr->filename = pop_here((*node)->here_doc);
			else
				curr->filename = xp_heredoc(pop_here((*node)->here_doc), env);
		}
		curr = curr->next;
	}
	return (0);
}

t_redirection	*get_parse_here_doc(t_token *token, t_env *env)
{
	t_redirection		*here_doc;
	t_token				*cursor;
	t_redirection_type	type;
	t_here_doc			*data;
	int					h_fd;

	cursor = token;
	here_doc = NULL;
	while (cursor && g_last_exit_status != 130)
	{
		if (cursor->type == DELIMITER || cursor->type == DELIMITER_NO_EXPEND)
		{
			data = init_data(&cursor->value, temp_filename(), token, here_doc);
			h_fd = handle_heredoc(data, env);
			type = get_type_here_doc(cursor->type);
			if (h_fd > 0)
				close(h_fd);
			ft_redirectionadd_back(&here_doc, \
				ft_redirection_new(data->filename, type));
			free(data);
		}
		cursor = cursor->next;
	}
	return (here_doc);
}
