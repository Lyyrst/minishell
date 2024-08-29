/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilercard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:42:41 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:22:32 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a file name matches a wildcard filter.
 *
 * @param d_name The file name.
 * @param filtre The wildcard filter.
 * @return 1 if the file name matches the filter, otherwise 0.
 */
size_t	get_size_w(char *directory_path)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			total_size;

	total_size = 0;
	dir = opendir(directory_path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (!((ft_strcmp(entry->d_name, ".") == 0 \
			|| ft_strcmp(entry->d_name, "..") == 0)))
		{
			if (entry->d_name[0] != '.')
			{
				total_size += ft_strlen(entry->d_name);
				total_size++;
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (total_size);
}

/**
 * Process the expansion of a wildcard entry.
 *
 * @param entry The directory entry to process.
 * @param value The value containing the wildcard.
 * @param res 	A pointer to the result string.
 * @param found A pointer to the flag indicating if any matches were found.
 */
int	process_expend_wilercard(struct dirent *e, char *v, char **res)
{
	if (!((ft_strcmp(e->d_name, ".") == 0 || \
			ft_strcmp(e->d_name, "..") == 0)))
	{
		if (e->d_name[0] != '.')
		{
			if (is_valide_filtre(e->d_name, v))
			{
				ft_strcat(*res, e->d_name);
				ft_strcat(*res, " ");
				return (1);
			}
		}
	}
	return (0);
}

int	get_num_w(char *input)
{
	int	i;

	i = 0;
	while (*input)
	{
		if (*input == '*')
			i++;
		input++;
	}
	return (i);
}

char	*process_wil(DIR *dir, char *value)
{
	char			*expend_value;
	struct dirent	*entry;
	int				found;
	char			*pwd;

	found = 0;
	pwd = getcwd(NULL, 0);
	expend_value = malloc(sizeof(char) * \
					(((get_size_w(pwd) * 2) * get_num_w(value)) + 1));
	free(pwd);
	if (!expend_value)
		return (NULL);
	expend_value[0] = '\0';
	entry = readdir(dir);
	while (entry)
	{
		found += process_expend_wilercard(entry, value, &expend_value);
		entry = readdir(dir);
	}
	if (found == 0)
		ft_strcat(expend_value, value);
	return (expend_value);
}

/**
 * Expand wildcards in a given value.
 *
 * @param value The string containing the wildcard.
 * @return A new string with the expanded wildcard, or NULL on failure.
 */
char	*expend_wilercard(char *value)
{
	DIR				*dir;
	char			*pwd;
	char			*expend_value;

	pwd = getcwd(NULL, 0);
	dir = opendir(pwd);
	free(pwd);
	if (!dir)
		return (0);
	expend_value = process_wil(dir, value);
	closedir(dir);
	return (expend_value);
}
