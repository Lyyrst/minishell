/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:23:12 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:46:22 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds a character to the result string as part of the 
 * variable expansion.
 *
 * @param params 	The parameters for variable expansion.
 * @param c 		The character to be added to the result string.
 */
void	add_char_to_result(t_expansion_params *params, char c)
{
	char	*tmp;
	char	*value;

	value = malloc(sizeof(char) * 2);
	value[0] = c;
	value[1] = 0;
	tmp = (*params->result);
	(*params->result) = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	(*params->i)++;
}

/**
 * If necessary, add quotation marks around the given value.
 * To avoid executing meta char from export
 *
 * @param value	The value to potentially enclose in quotes.
 * @return		A new string with the value enclosed in quotation marks 
 * if necessary. Returns NULL on memory allocation failure.
 */
char	*quote_value_if_needed(const char *value)
{
	char	*quoted_value;
	int		i;
	int		j;

	quoted_value = malloc(ft_strlen(value) * 3 + 1);
	if (!quoted_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '|' || value[i] == '<' \
			|| value[i] == '>' || value[i] == '\'')
			process_quote_if_needed(&value, &i, &quoted_value, &j);
		else if (value[i] == '\"')
			process_s_quote_if_needed(&value, &i, &quoted_value, &j);
		else
			quoted_value[j++] = value[i++];
	}
	quoted_value[j] = '\0';
	return (quoted_value);
}

/**
 * Expands the output code stored in `g_last_exit_status` to a string,
 * and adds it to the expansion result.
 *
 * @param params	The structure containing the expansion parameters,
 * 					including result buffer and path indices.
 */
void	expand_exit_status(t_expansion_params *params)
{
	char	*exit_status_str;
	char	*tmp;

	exit_status_str = ft_itoa(g_last_exit_status);
	if (!exit_status_str)
		return ;
	tmp = (*params->result);
	(*params->result) = ft_strjoin(tmp, exit_status_str);
	free(tmp);
	free(exit_status_str);
	*params->i += 2;
}

static void	process_ft_expend(char **sp, int *i, char **res, t_env *env)
{
	char	*tmp;

	if (ft_strcmp(sp[(*i)], "<<") == 0)
	{
		*res = ft_strjoin_free(*res, sp[(*i)++]);
		*res = ft_strjoin_free(*res, " ");
		if (sp[(*i)])
		{
			*res = ft_strjoin_free(*res, sp[(*i)++]);
			*res = ft_strjoin_free(*res, " ");
		}
		return ;
	}
	tmp = ft_expand_envvar(sp[(*i)++], env);
	*res = ft_strjoin_free(*res, tmp);
	*res = ft_strjoin_free(*res, " ");
	free(tmp);
}

char	*ft_expend(char **split_input, t_env *env)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, sizeof(char));
	if (!split_input || !res)
		return (NULL);
	while (split_input[i])
		process_ft_expend(split_input, &i, &res, env);
	return (res);
}
