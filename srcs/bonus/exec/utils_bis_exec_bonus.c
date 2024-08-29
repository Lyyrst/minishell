/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis_exec_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:49:08 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:51:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_here_doc(t_ast_node **node, t_env **env, t_redirection **here_doc)
{
	t_token		*tokens;
	char		*file_name;
	t_token		*tmp;

	tokens = lexer((*node)->token->value, *env);
	tmp = tokens;
	while (tokens)
	{
		if (tokens->type == DELIMITER || tokens->type == DELIMITER_NO_EXPEND)
		{
			file_name = pop_here(here_doc);
			free(file_name);
		}
		tokens = tokens->next;
	}
	free_tokens(tmp);
}
