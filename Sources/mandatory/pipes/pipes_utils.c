/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:35:30 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 18:08:58 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Clears the data and returns the right error message and code if execve 
 * failed.
 * @param path_cmd A pointer that needs to be freed
 * @param args_cmd A pointer that needs to be freed
 * @param env A pointer that needs to be freed
*/
int	execve_fail(char *path_cmd, char **args_cmd, char **env)
{
	perror(path_cmd);
	free(path_cmd);
	free_tabtab(args_cmd);
	free_tabtab(env);
	exit(errno);
}

/**
 * Calculates the size of the given list.
 * @param list The list we want the size of.
*/
int	size_list(t_env_list **list)
{
	int			len;
	t_env_list	*tmp;

	len = 0;
	if (list == NULL)
		return (0);
	tmp = *list;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	command_not_found(t_exec *exec_struct, t_table *table, char *path_cmd)
{
	write(2, table->cmd, ft_strlen(table->cmd));
	write(2, ": Command not found\n", 20);
	free_process(*exec_struct, path_cmd, NULL, NULL);
	exit(127);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned int)s1[i] - (unsigned int)s2[i]);
}
