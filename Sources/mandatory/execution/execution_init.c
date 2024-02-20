/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:06:00 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:08:59 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Initialize our execution structure.
 * @param exec_struct The execution struction we are initializing.
 * @param envp TEMP PARAM BCS IN t_struct.
*/
int	init_exec_struct(t_exec *exec_struct, t_shell *shell, char **envp)
{
	exec_struct->export_list = NULL;
	exec_struct->shell = shell;
	exec_struct->export_list = malloc(sizeof(t_env_list *));
	if (exec_struct->export_list == NULL)
		return (0);
	*(exec_struct->export_list) = init_list(*(exec_struct->export_list),
			envp);
	if (*(exec_struct->export_list) == NULL && *envp != NULL)
		return (0);
	sort_export_list(exec_struct->export_list);
	return (1);
}

/**
 * Filling the list of our environment variables with the env variable 
 * from main. On error, returns NULL. On success, returns the address of 
 * the first environment variable.
 * @param list The first element of our list of variable environment.
 * @param env Our environment variable.
*/
t_env_list	*init_list(t_env_list *list, char **env)
{
	int		i;
	int		sep;
	char	*name;
	char	*value;

	i = 0;
	sep = 0;
	list = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		sep = search_char(env[i], '=');
		name = ft_substr(env[i], 0, sep);
		value = ft_substr(env[i], sep + 1, ft_strlen(env[i]));
		if (name == NULL || value == NULL || add_node(&list, name, value) == 0)
		{
			free(name);
			free(value);
			free_list(&list);
			return (NULL);
		}
		i++;
	}
	return (list);
}

void	init_filling_heredoc(t_filling_heredoc *heredoc)
{
	heredoc->line = NULL;
	heredoc->filename = NULL;
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	heredoc->expand = 1;
	heredoc->fd = -1;
}

t_pipex	*init_pipex(t_exec *exec_struct, int nb_cmd)
{
	int		i;
	int		*pid;
	int		**fd;
	t_pipex	*pipex;

	i = 0;
	pid = malloc(nb_cmd * sizeof(int));
	if (pid == NULL)
		return (perror("malloc"), NULL);
	fd = create_pipex_fd(pid, nb_cmd);
	if (fd == NULL)
		return (NULL);
	while (i < nb_cmd - 1)
		if (pipe(fd[i++]) == -1)
			return (error_forking(pid, fd, i), NULL);
	pipex = malloc(sizeof(t_pipex));
	if (pipex == NULL)
		return (error_forking(pid, fd, i), NULL);
	pipex->fd = fd;
	pipex->pid = pid;
	pipex->nb_cmd = nb_cmd;
	pipex->exec_struct = exec_struct;
	pipex->nb_child = 0;
	return (pipex);
}
