/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberkrou <bberkrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:20:10 by bberkrou          #+#    #+#             */
/*   Updated: 2024/04/05 15:33:30 by bberkrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pop_here(t_redirection **here_doc)
{
	char			*filename;
	t_redirection	*tmp;

	if (!*here_doc)
	{
		printf("ERROR\n");
		exit(1);
	}
	filename = ft_strdup((*here_doc)->filename);
	free((*here_doc)->filename);
	tmp = *here_doc;
	*here_doc = (*here_doc)->next;
	free(tmp);
	return (filename);
}

void	print_error_heredoc(char *delimiter)
{
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file \
			(wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

int	get_random_number(int limits)
{
	static int	counter;
	int			random;

	if (!counter)
		counter = 8;
	counter = counter * 61 + 91;
	random = (counter / 127) % 37;
	return ((unsigned int)random % limits);
}

char	*get_valide_name(struct dirent *entry, DIR **dir)
{
	char			*rdm_val;
	char			*temp_file_name;

	rdm_val = ft_uitoa_base((unsigned long long) \
		get_random_number((214748)), "{7-*$>|&");
	temp_file_name = ft_strjoin("/tmp/minishell_heredoc_", rdm_val);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, temp_file_name) != 0)
		{
			free(rdm_val);
			return (temp_file_name);
		}
		entry = readdir(*dir);
	}
	free(rdm_val);
	free(temp_file_name);
	return (NULL);
}

/**
 * Generates a temporary fd name based on a given fd.
 *
 * @param fd	The fd to be used to generate the temporary file name.
 * @return 		A pointer to the character string containing 
 * 				the generated temporary file name.
 */
char	*temp_filename( void )
{
	char			*temp_file_name;
	char			*pwd;
	struct dirent	*entry;
	DIR				*dir;

	pwd = getcwd(NULL, 0);
	dir = opendir(pwd);
	free(pwd);
	if (!dir)
		return (0);
	entry = readdir(dir);
	temp_file_name = get_valide_name(entry, &dir);
	while (temp_file_name == NULL)
		temp_file_name = get_valide_name(entry, &dir);
	closedir(dir);
	return (temp_file_name);
}
