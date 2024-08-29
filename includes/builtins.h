/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:17:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:54:12 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int			is_builtins(t_token *token);
int			exec_builtins(t_token *token, t_env **env, t_ast_node *node, \
							int fd_dup[2]);

int			ft_env(char **argv, t_env *env);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(char **args, t_env *env);
int			ft_echo(char **args, t_env *env);

int			ft_unset(char **args, t_env **env);
int			ft_export(char **args, t_env **env);
int			ft_exit(char **args, t_env *env, t_ast_node *node, int fd_dup[2]);

void		append_env(char *value, char *old_key, t_env **env, int n);
int			is_equal(char *str);
int			ft_export_env(t_env *env);
char		**ft_split_export(char *str);
void		print_export(t_env **env);
void		check_exit_args(char **args, t_env *env, t_ast_node *ast, \
								int fd_dup[2]);
void		clear_exit(char **args, t_env *env, t_ast_node *ast, int fd_dup[2]);
void		print_exit_error(char *str, int n);

long long	ft_atoll(const char *str);
int			max_long(char **args);
int			alpha_args(char **args);

#endif