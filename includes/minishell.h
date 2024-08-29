/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:45:18 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:21:49 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../srcs/libft/libft.h"

# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

# include "env.h"
# include "parsing.h"
# include "ast.h"
# include "here_doc.h"
# include "exec.h"
# include "builtins.h"
# include "signal_utils.h"
# include "utils.h"

# define BONUS_USED 1

# ifdef BONUS_USED
#  include "bonus/parsing_bonus.h"
#  include "bonus/ast_bonus.h"
#  include "bonus/wilercard_bonus.h"
#  include "bonus/exec_bonus.h"

char	*get_cmd(t_env *env);
int		get_tokens_list(char *command, t_token **tokens);
int		get_first_ast(t_token *tokens, t_ast_node **ast);
int		get_expend_ast(t_ast_node **ast, t_env *env);
int		get_is_valide_ast(t_ast_node **ast, t_env *env);

# endif

extern int	g_last_exit_status;

void	print_token(t_token *tokens);
void	print_tokens(t_token *tokens);
void	print_ast(t_ast_node *node, int level);
void	print_split_input(char **split_input);
void	get_history(int argc, char **argv);
void	add_to_history(char *cmd);

int		get_fd(t_redirection *redirections);
void	replace_heredocs_with_infiles(t_redirection *redirections);
#endif
