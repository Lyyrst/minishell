/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:59 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:49:57 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_wilecrad_error(t_token *cursor, char **ag_spl, char *args)
{
	ft_free_tab(ag_spl);
	free(args);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cursor->value, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (0);
}

void	replace_file_wilcard(t_token **c, char **ag_spl)
{
	free((*c)->value);
	(*c)->value = ft_strdup(ag_spl[0]);
}

int	check_and_replace_redirection_wilcard(t_token **tokens)
{
	t_token	*c;
	char	*args_wilercard;
	char	**ag_spl;

	c = *tokens;
	while (c)
	{
		if ((c->type == INFILE || c->type == OUTFILE || c->type == APPENDFILE) \
			&& ft_strchr(c->value, '*') != NULL)
		{
			args_wilercard = expend_wilercard(c->value);
			if (!args_wilercard)
				return (0);
			ag_spl = ft_split(args_wilercard, ' ');
			if (ag_spl[0] && ag_spl[1] == 0)
				replace_file_wilcard(&c, ag_spl);
			else if (ag_spl[0] && ag_spl[1])
				return (print_wilecrad_error(c, ag_spl, args_wilercard));
			ft_free_tab(ag_spl);
			free(args_wilercard);
		}
		c = c->next;
	}
	return (1);
}

void	process_expend_ast_execute(t_ast_node **node, t_env **env, \
	t_redirection **here_doc)
{
	t_ast_node	*tmp;
	t_token		*tokens;
	t_token		*tmp_tokens;
	t_ast_node	*new_ast;

	tmp = (*node);
	tokens = lexer((*node)->token->value, *env);
	if (tokens->type == WILERCARD)
	{
		replace_wilercard(&tokens);
		tmp_tokens = tokens;
		tokens = tokens->next;
		free_token(tmp_tokens);
	}
	if (!check_and_replace_redirection_wilcard(&tokens))
	{
		free_tokens(tokens);
		return ;
	}
	new_ast = build_ast(&tokens, here_doc);
	new_ast->parent = (*node)->parent;
	(*node) = new_ast;
	process_ft_free_ast(tmp);
	execute_ast(new_ast, env);
}

/**
 * Execute the AST with logical operators AND and OR and ().
 *
 * @param node The current node of the AST.
 * @param env The environment variables.
 */
void	execute_ast_bonus(t_ast_node **node, t_env **env, \
	t_redirection **here_doc)
{
	if (!node || !*node)
		return ;
	if ((*node)->type == AND)
	{
		execute_ast_bonus(&(*node)->left, env, here_doc);
		if (g_last_exit_status == 0)
			execute_ast_bonus(&(*node)->right, env, here_doc);
		else
			clear_here_doc(&(*node)->right, env, here_doc);
	}
	else if ((*node)->type == OR)
	{
		execute_ast_bonus(&(*node)->left, env, here_doc);
		if (g_last_exit_status != 0 && g_last_exit_status != 130)
			execute_ast_bonus(&(*node)->right, env, here_doc);
		else
			clear_here_doc(&(*node)->right, env, here_doc);
	}
	else
		process_expend_ast_execute(node, env, here_doc);
}
