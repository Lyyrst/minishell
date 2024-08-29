/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:11:37 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 03:25:19 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_SPLIT_H
# define PARSING_SPLIT_H

void	add_pipe(char **input, char ***split_input, int *i);
void	add_redirection_operator(char **input, char ***split_input, int *i);
void	add_word(char **input, char ***split_input, int *i);

int		check_split_input(char **split_input);
char	**ft_split_input(char *input);
char	*expend_val(t_token *token, t_env *env);
t_token	*re_split_tokens(t_token *tokens);
t_token	*pre_tokens(char **split_input, t_env *env);

#endif