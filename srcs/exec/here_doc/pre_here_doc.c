/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:24:20 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:31:11 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Pre-processes here-documents in the abstrakte syntax tree (AST).
 *
 * @param root 	The root node of the abstract syntax tree (AST).
 * @param env 	The env structure containing env var.
 * @return 		1 if an error has occurred during pre-processing. 
 * 				here-documents, otherwise 0.
 */
int	pre_process_heredocs(t_ast_node **root, t_env *env)
{
	if (!root || !*root)
		return (0);
	if ((*root)->type == CMD || (*root)->type == HERE_DOC)
		if (process_heredocs(root, env))
			return (1);
	if (pre_process_heredocs(&((*root)->left), env))
		return (1);
	return (pre_process_heredocs(&((*root)->right), env));
}

void	process_write_heredoc(char *line, char *delimiter, int fd, t_env *env)
{
	(void)env;
	while (line && g_last_exit_status != -2147483648)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
		{
			if (g_last_exit_status != -2147483648)
			{
				ft_putnbr_fd(g_last_exit_status, 2);
				print_error_heredoc(delimiter);
			}
			break ;
		}
	}
	free(line);
}
