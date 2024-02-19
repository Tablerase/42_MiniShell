/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:00:20 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 13:48:23 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

/**
 * Frees all the allocated memory of a child process.
 * @param exec_struct The structure passed to each process.
 * @param path A pointer that should have been given to execve but an error 
 * occured before, therefore we should free it.
 * @param arg A pointer that should have been given to execve but an error 
 * occured before, therefore we should free it.
 * @param env A pointer that should have been given to execve but an error 
 * occured before, therefore we should free it.
*/
void	free_process(t_exec exec_struct, char *path, char **arg, char **env)
{
	free_exec_struct(exec_struct);
	if (path != NULL)
		free(path);
	free_tabtab(arg);
	free_tabtab(env);
}

/**
 * Frees a pointer to strings.
 * @param str The pointer we are freeing.
*/
void	free_tabtab(char **str)
{
	int	i;

	if (str != NULL)
	{
		i = 0;
		while (str[i] != NULL)
			free(str[i++]);
		free(str);
	}
}

/**
 * Frees all the data present in the t_exec structure.
 * @param exec_struct The structure we want to free.
*/
void	free_exec_struct(t_exec exec_struct)
{
	free_list(exec_struct.env_list);
	free(exec_struct.env_list);
	free_list(exec_struct.export_list);
	free(exec_struct.export_list);
	free_shell(exec_struct.shell);
	free(exec_struct.shell);
}

/**
 * Frees our list of environment variable.
 * @param list The head of our environment variable list.
*/
void	free_list(t_env_list **list)
{
	t_env_list	*tmp;

	if (list == NULL)
		return ;
	tmp = *list;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		free((*list)->name);
		free((*list)->value);
		free((*list));
		(*list) = tmp;
	}
}

/**
 * TEMP FUNCTION
*/
void	free_shell(t_shell *shell)
{
	int		i;
	t_table	*tmp;

	i = 0;
	dup2(shell->std_in, 0);
	close(shell->std_in);
	dup2(shell->std_out, 1);
	close(shell->std_out);
	while (shell->table_head != NULL)
	{
		if (shell->table_head->infile != NULL)
		{
			while (shell->table_head->infile[i] != NULL)
				free(shell->table_head->infile[i++]);
			free(shell->table_head->infile);
		}
		i = 0;
		while (shell->table_head->args[i] != NULL)
			free(shell->table_head->args[i++]);
		free(shell->table_head->args);
		i = 0;
		if (shell->table_head->outfile != NULL)
		{
			while (shell->table_head->outfile[i] != NULL)
			{
				free(shell->table_head->outfile[i]->file);
				free(shell->table_head->outfile[i++]);
			}
		}
		if (shell->table_head->outfile != NULL)
			free(shell->table_head->outfile);
		tmp = shell->table_head;
		shell->table_head = shell->table_head->next;
		free(tmp);
	}
}
