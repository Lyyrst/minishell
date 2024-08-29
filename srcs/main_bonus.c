/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 00:59:00 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:51:07 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ast(t_token *tokens, t_ast_node **ast, t_env *env)
{
	if (!get_first_ast(tokens, ast))
		return (0);
	if (!get_expend_ast(ast, env))
		return (0);
	if (!get_is_valide_ast(ast, env))
		return (0);
	return (1);
}

int	get_here(t_ast_node *ast, t_env *env, t_redirection **here_doc)
{
	if (g_last_exit_status == 130)
		g_last_exit_status = -130;
	get_parse_hd_bonus(&ast, env, here_doc);
	if (g_last_exit_status == 130)
	{
		ft_free_redirection(*here_doc);
		*here_doc = NULL;
		ft_free_ast(ast);
		return (0);
	}
	if (g_last_exit_status == -130)
		g_last_exit_status = 130;
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	char			*command;
	t_token			*tokens;
	t_ast_node		*ast;
	t_env			*env;
	t_redirection	*here_doc;

	here_doc = NULL;
	env = ft_env_to_struct(envp);
	get_history(argc, argv);
	while (g_last_exit_status >= 0)
	{
		command = get_cmd(env);
		if (!command)
			break ;
		if (ft_strlen(command) == 0 || !get_tokens_list(command, &tokens) \
			|| !get_ast(tokens, &ast, env) || !get_here(ast, env, &here_doc))
			continue ;
		execute_ast_bonus(&ast, &env, &here_doc);
		if (ast->here_doc)
			ft_free_redirection(*(ast->here_doc));
		ft_free_ast(ast);
	}
	if (env)
		free_env(env);
	return (g_last_exit_status);
}
