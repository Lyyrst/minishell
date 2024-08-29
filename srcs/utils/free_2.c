/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:02:52 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 10:02:58 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_token(t_token *tokens)
{
	if (!tokens)
		return ;
	free(tokens->value);
	free(tokens);
}

void	ft_free_fork(t_ast_node *node, t_env *env)
{
	ft_free_ast(node);
	free_env(env);
}

void	ft_free_redirection_node(t_redirection *redirection)
{
	t_redirection	*tmp;

	if (!redirection)
		return ;
	while (redirection)
	{
		tmp = redirection;
		redirection = redirection->next;
		free(tmp);
	}
}
