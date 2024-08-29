/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:12:05 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:51:44 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_heredoc_bonus(t_here_doc *data, t_env *env, t_ast_node **root, \
						t_redirection **hd)
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
		ft_free_redirection(*hd);
		ft_free_ast(*root);
		close(fd);
		if (g_last_exit_status == -2147483648)
			exit(130);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

int	handle_heredoc_bonus(t_here_doc *data, t_env *env, t_ast_node **root, \
							t_redirection **hd)
{
	int		tmp_fd;
	int		pid;
	int		err_code;

	pid = fork_heredoc_bonus(data, env, root, hd);
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

t_redirection	*get_parse_hd_bbonus(t_token *t, t_env *env, t_ast_node **r, \
										t_redirection **hd)
{
	t_redirection		*here_doc;
	t_token				*cursor;
	t_redirection_type	type;
	t_here_doc			*data;
	int					h_fd;

	cursor = t;
	here_doc = NULL;
	while (cursor && g_last_exit_status != 130)
	{
		if (cursor->type == DELIMITER || cursor->type == DELIMITER_NO_EXPEND)
		{
			data = init_data(&cursor->value, temp_filename(), t, here_doc);
			h_fd = handle_heredoc_bonus(data, env, r, hd);
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

void	process_get_parse_hd(t_ast_node **n, t_env *env, t_redirection **hd)
{
	t_token			*tokens;
	t_redirection	*new_here_doc;

	tokens = lexer((*n)->token->value, env);
	new_here_doc = get_parse_hd_bbonus(tokens, env, n, hd);
	free_tokens(tokens);
	ft_redirectionadd_back(hd, new_here_doc);
}

/**
 * Execute the AST with logical operators AND and OR and ().
 *
 * @param node The current node of the AST.
 * @param env The environment variables.
 */
void	get_parse_hd_bonus(t_ast_node **node, t_env *env, t_redirection **hd)
{
	if (!node || !*node)
		return ;
	if ((*node)->type == AND || (*node)->type == OR)
	{
		get_parse_hd_bonus(&(*node)->left, env, hd);
		get_parse_hd_bonus(&(*node)->right, env, hd);
	}
	else
		process_get_parse_hd(node, env, hd);
}
