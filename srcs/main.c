/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:05:17 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:03:15 by bberkrou         ###   ########.fr       */
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

int	get_tokens(char **command, t_env *env, t_token **tokens)
{
	*tokens = lexer(*command, env);
	if (!is_valide_lexer(*tokens, *command))
		return (0);
	return (1);
}

int	get_here_doc(t_redirection **here_doc, t_token **tokens, t_env *env)
{
	if (g_last_exit_status == 130)
		g_last_exit_status = -130;
	*here_doc = get_parse_here_doc(*tokens, env);
	if (g_last_exit_status == 130)
	{
		ft_free_redirection(*here_doc);
		free_tokens(*tokens);
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
	t_redirection	*here_doc;
	t_ast_node		*ast;
	t_env			*env;

	env = ft_env_to_struct(envp);
	get_history(argc, argv);
	while (g_last_exit_status >= 0)
	{
		command = get_cmd(env);
		if (!command)
			break ;
		if (ft_strlen(command) == 0 || !get_tokens(&command, env, &tokens))
			continue ;
		if (!get_here_doc(&here_doc, &tokens, env))
			continue ;
		ast = build_ast(&tokens, &here_doc);
		execute_ast(ast, &env);
		if (ast->here_doc)
			ft_free_redirection(*(ast->here_doc));
		process_ft_free_ast(ast);
	}
	free_env(env);
	return (0);
}
