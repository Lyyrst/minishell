/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:40 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:49:51 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_pipe
{
	t_ast_node	*node;
	t_env		*env;
	int			fd_in;
}	t_pipe;

int				exec_command(t_ast_node *r, int in_fd, int *p_fd, t_env *env);
int				handle_heredoc(t_here_doc *data, t_env *env);
int				check_find_path_var(char *path_var, char *cmd);
int				ft_is_a_directory(char *cmd);
char			**get_args(t_token *token);
char			*ft_get_path(t_token *token, t_env *env);
char			*pop_here(t_redirection **here_doc);
void			execute_ast(t_ast_node *root, t_env **envp);
void			exec_pipeline(t_ast_node *node, t_env *env, int fd_in);
void			process_exec_cmd_builtins(t_ast_node *root, t_env *env, \
											int fd_dup[2]);
void			exec_builtins_no_fork(int pipe_fds[2], t_ast_node *root, \
											t_env **env);
void			process_exec_fd_dup(int in_fd, int pipe_fds[2]);
void			*no_such_file(char *cmd);
void			clear_here_doc(t_ast_node **node, t_env **env, \
							t_redirection **here_doc);
void			ft_error_no_path(char **paths, t_env *env, char *cmd);
void			process_exec_fd(int in_fd, int pipe_fds[2], \
							t_ast_node *node, t_env *env);
t_redirection	*get_parse_here_doc(t_token *token, t_env *env);
#endif