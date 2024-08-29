/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:49:43 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:25:08 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

typedef struct s_here_doc {
	char			**delimiter;
	char			*filename;
	t_token			*token;
	t_redirection	*here_doc;
}	t_here_doc;

int					process_heredocs(t_ast_node **node, t_env *env);
int					pre_process_heredocs(t_ast_node **root, t_env *env);
char				*temp_filename( void );
char				*xp_heredoc(char *filename, t_env *env);
char				*pop_here(t_redirection **here_doc);
void				process_write_heredoc(char *line, char *delimiter, int fd, \
											t_env *env);
void				print_error_heredoc(char *delimiter);
void				process_write_heredoc(char *line, char *delimiter, int fd, \
											t_env *env);
void				write_heredoc(char *delimiter, t_env *env, int fd);
void				free_fork_here_doc(t_here_doc *data, t_env *env);
t_here_doc			*init_data(char **delimiter, char *filename, \
						t_token *token, t_redirection *here_doc);
t_redirection_type	get_type_here_doc(t_token_type type);
#endif