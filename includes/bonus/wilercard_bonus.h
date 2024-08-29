/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilercard_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:26:29 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/02 15:04:57 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILERCARD_BONUS_H
# define WILERCARD_BONUS_H

# include "../minishell.h"

void	sort_wilercard(t_token **token);
size_t	get_size_w(char *directory_path);
char	*expend_wilercard(char *value);
int		get_args_number(t_token *token);
int		counter_wilercard(char *filtre);
int		get_return_filter_wilercard(char *filtre, char *d_name, int i, int j);
int		replace_wilercard(t_token **token);
int		is_valide_filtre(char *d_name, char *filtre);
int		is_swap(t_token *token1, t_token *token2);
int		get_val(char c);

#endif
