/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:04:49 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:28:10 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Try to check if a token is a builtins
 *
 * @param token A pointer to the token representing the command.
 * @return 		If the token is a builtins
 */
int	is_builtins(t_token *token)
{
	char	*value;

	value = token->value;
	return (ft_strcmp(value, "env") == 0
		|| ft_strcmp(value, "pwd") == 0
		|| ft_strcmp(value, "echo") == 0
		|| ft_strcmp(value, "cd") == 0
		|| ft_strcmp(value, "exit") == 0
		|| ft_strcmp(value, "export") == 0
		|| ft_strcmp(value, "unset") == 0);
}

/**
 * Executes built-in commands according to the given token.
 *
 * @param token A pointer to the token representing the command.
 * @param env 	A pointer to the environment structure.
 * @return 		The output code of the command executed, or -1 in the 
 * 				event of an error.
 */
int	exec_builtins(t_token *token, t_env **env, t_ast_node *root, int fd_dup[2])
{
	char	**args;
	int		exit_code;

	(void)fd_dup;
	exit_code = 0;
	args = get_args(token);
	if (!args)
		return (-1);
	if (ft_strcmp(token->value, "echo") == 0)
		exit_code = ft_echo(args, *env);
	if (ft_strcmp(token->value, "cd") == 0)
		exit_code = ft_cd(args, *env);
	if (ft_strcmp(token->value, "env") == 0)
		exit_code = ft_env(args, *env);
	if (ft_strcmp(token->value, "exit") == 0)
		exit_code = ft_exit(args, *env, root, fd_dup);
	if (ft_strcmp(token->value, "export") == 0)
		exit_code = ft_export(args, env);
	if (ft_strcmp(token->value, "pwd") == 0)
		exit_code = ft_pwd(args, *env);
	if (ft_strcmp(token->value, "unset") == 0)
		exit_code = ft_unset(args, env);
	ft_free_tab(args);
	return (exit_code);
}
