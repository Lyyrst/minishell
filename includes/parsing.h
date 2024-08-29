/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:28:02 by bberkrou          #+#    #+#             */
/*   Updated: 2024/03/30 16:13:07 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "parsing_export.h"
# include "parsing_quotes.h"
# include "parsing_split.h"
# include "parsing_tocken.h"

t_token	*lexer(char *input, t_env *env);
t_token	*tokenize(t_token *tokens);
void	replace_no_nvar(t_token **token);

int		syntaxer(t_token *tokens);

char	**ft_clean_input(char **split_input);
int		get_meta_char(char *c);
char	**split_and_or(char *input);
void	skip_spaces(char **input);
void	add_word(char **input, char ***split_input, int *i);

#endif
