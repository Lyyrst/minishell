/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:19:40 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:26:08 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print;
	struct s_env	*next;
}	t_env;

int		search_in_env(char *key, t_env *env);
int		ft_arraylen(char **strings);
int		get_total_lenght(char **strings);
int		search_var_in_env(char *key, t_env *env);
int		remove_var_if_first(char *key, t_env **env);
char	**ft_env_to_array(t_env *env);
char	*ft_getenv(char *key, t_env *env);
void	export_upadte_env(char *value, char *key, t_env **env, int n);
void	upadte_env(char *value, char *key, t_env *env, int n);
void	remove_var_in_env(char *key, t_env **env);
void	ft_env_add_back(t_env **lst, t_env *new);
void	complete_environment(t_env **env);
t_env	*ft_env_to_struct(char **envp);
t_env	*ft_env_last(t_env *lst);
t_env	*ft_env_new(char *key, char *value, int n);

#endif 
