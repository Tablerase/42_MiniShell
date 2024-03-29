/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execve_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:31:08 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 08:18:53 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Returns the current value of the PATH environment variable 
 * (if it has not been unseted).
 * @param env_list The list of environment variables of our program.
 * @param cmd The command we want to find.
*/
char	*find_path(t_env_list **env_list, char *cmd)
{
	char	*path;

	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = ft_getenv("PATH", env_list);
	if (path == NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = search_path(path, cmd);
	return (path);
}

/**
 * Searches the absolute path of the command we are willing to execute.
 * If it is found, this path is returned. Else NULL is returned.
 * @param path The value of the PATH environment variable.
 * @param cmd The command we are searching for.
*/
char	*search_path(char *path, char *cmd)
{
	int		i;
	char	**split_path;

	i = 0;
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		return (NULL);
	while (split_path[i] != NULL)
	{
		path = try_path(split_path[i], cmd);
		if (path != NULL)
		{
			if (access(path, F_OK) == 0)
				return (free_tabtab(split_path), path);
			free(path);
		}
		i++;
	}
	free_tabtab(split_path);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/**
 * Builts the absolute path with a part of PATH.
 * @param first_part The first part of the absolute path.
 * @param cmd The command we will add at the end of our string.
*/
char	*try_path(char *first_part, char *cmd)
{
	char	*tmp_path;
	char	*path;

	tmp_path = ft_strjoin(first_part, "/");
	if (tmp_path == NULL)
		return (NULL);
	path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	if (path == NULL)
		return (NULL);
	return (path);
}
