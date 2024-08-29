/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:47:35 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 18:16:02 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 0;

/**
 * Extracts the name of an environment variable from an input string.
 *
 * @param input	The input string containing the variable name.
 * @param index	A pointer to the current index in the input string.
 *				This index is updated to point after the extracted name.
 *
 * @return The name of the extracted environment variable.
 */
char	*extract_var_name(const char *input, int *index)
{
	int		start;
	int		len;
	char	*var_name;

	len = 0;
	start = *index + 1;
	while (input[start + len]
		&& (isalnum(input[start + len]) || input[start + len] == '_'))
		len++;
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, input + start, len);
	var_name[len] = '\0';
	*index = start + len;
	return (var_name);
}

/**
 * Retrieves the value of a given environment variable.
 * 
 * @param var_name The name of the environment variable whose value you wish to 
 * the value of.
 * 
 * @return	The value of the environment variable if it exists, 
 *			otherwise an empty string.
 */
char	*get_var_value(char *var_name, t_env *env)
{
	char	*value;
	char	*quoted_value;

	value = ft_getenv(var_name, env);
	if (!value)
		return (ft_strdup(""));
	quoted_value = quote_value_if_needed(value);
	free(value);
	return (quoted_value);
}

/**
 * Expands the value of a given environment variable by searching for it
 * by name, then adding this value to the expansion result.
 *
 * @param input		The input string from which the variable's * name is extracted. 
 * 					variable is extracted.
 * @param params	The structure containing the expansion parameters,
 *					including the result buffer and 
 *					path indices.
 */
static void	expand_env_variable(const char *input, t_expansion_params *params
	, t_env *env)
{
	char	*var_name;
	char	*value;
	char	*tmp;

	(void)env;
	var_name = extract_var_name(input, params->i);
	if (!var_name)
		return ;
	value = get_var_value(var_name, env);
	tmp = (*params->result);
	(*params->result) = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	free(var_name);
}

/**
 * Handles the expansion of environment variables in an input string,
 * by calling the appropriate functions to handle the expansion of 
 * each variable.
 *
 * @param input		The input string containing the environment 
 * 					variables to be expanded.
 * @param params 	The structure containing the expansion parameters,
 * 					including result buffer and path indices.
 */
void	handle_variable_expansion(const char *input, t_expansion_params *par
	, t_env *env)
{
	if (input[*par->i] == '$' && *par->in_single_quote != 1)
	{
		if (input[*par->i + 1] == '?')
			expand_exit_status(par);
		else if ((input[*par->i + 1] == '"' || input[*par->i + 1] == '\'')
			&& *par->in_single_quote == 0)
			expand_env_variable(input, par, env);
		else if (!ft_isalpha(input[*par->i + 1]) && input[*par->i + 1] != '_')
		{
			add_char_to_result(par, input[*par->i]);
			if (input[*par->i] == '$')
				add_char_to_result(par, input[*par->i]);
		}
		else if (input[*par->i + 1] != ' ' && input[*par->i + 1] != '\0'
			&& *par->in_single_quote != 1)
			expand_env_variable(input, par, env);
		else
		{
			add_char_to_result(par, input[*par->i]);
			if (input[*par->i] == '$')
				*par->i += 1;
		}
	}
	else
		add_char_to_result(par, input[*par->i]);
}

/**
 * Scans an input string to expand all the environment 
 * environment variables it contains, including the special 
 * special output code `$?`.
 *
 * @param input	The input string to be processed for variable 
 *				variables.
 *
 * @return		A new string containing the result of the 
 * 				variable expansion.
 */
char	*ft_expand_envvar(const char *input, t_env *env)
{
	char				*result;
	int					i;
	int					j;
	int					in_single_quote;
	t_expansion_params	params;

	result = malloc(sizeof(char) * 1);
	result[0] = 0;
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quote = 0;
	params.result = &result;
	params.i = &i;
	params.j = &j;
	params.in_single_quote = &in_single_quote;
	while (input[i])
	{
		handle_quotes(input[i], &in_single_quote);
		if (input[i])
			handle_variable_expansion(input, &params, env);
	}
	return (result);
}
