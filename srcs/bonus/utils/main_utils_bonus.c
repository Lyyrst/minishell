/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:49:10 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/04 20:46:52 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_env *env)
{
	char	*prompt;
	char	*command;

	setup_signal();
	prompt = build_prompt(env);
	command = readline(prompt);
	add_to_history(command);
	free(prompt);
	if (!command)
	{
		ft_putstr_fd("exit\n", 1);
		free_env(env);
		exit(g_last_exit_status);
	}
	add_history(command);
	return (command);
}

int	get_tokens_list(char *command, t_token **tokens)
{
	*tokens = lexer_bonus(command);
	if (!tokens || !*tokens)
		return (0);
	free(command);
	return (1);
}

int	get_first_ast(t_token *tokens, t_ast_node **ast)
{
	*ast = build_ast_bonus(&tokens);
	if (!ast)
	{
		free_tokens(tokens);
		return (0);
	}
	return (1);
}

int	get_expend_ast(t_ast_node **ast, t_env *env)
{
	int	valide_ast;

	valide_ast = 1;
	expend_ast(ast, env, &valide_ast);
	if (valide_ast == 0 || valide_ast == 2)
	{
		ft_free_ast(*ast);
		return (0);
	}
	return (1);
}

int	get_is_valide_ast(t_ast_node **ast, t_env *env)
{
	int	valide_ast;

	valide_ast = 1;
	check_ast_syntaxe(*ast, &valide_ast);
	if (valide_ast == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `('\n", 2);
		g_last_exit_status = 2;
		ft_free_ast(*ast);
		return (0);
	}
	check_ast_syntaxe_mandatory(*ast, &valide_ast, env);
	if (valide_ast == 0)
	{
		ft_free_ast(*ast);
		return (0);
	}
	return (1);
}
