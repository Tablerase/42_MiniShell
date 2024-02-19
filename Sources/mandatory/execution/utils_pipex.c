/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:39:40 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 19:05:30 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	error_forking(int *pid, int **fd, int i)
{
	{
		while (--i >= 0)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		free(fd);
		free(pid);
		return (NULL);
	}
	perror("fork");
}

void	clear_all_fds(int **fd, int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	exit_child_process(t_pipex *pipex, int status)
{
	free_exec_struct(*(pipex->exec_struct));
	free(pipex->pid);
	free(pipex);
	if (status >= 0)
		exit(status);
	return (1);
}

void	redirect_into_pipes(t_pipex *pipex, int nb_child)
{
	if (nb_child == 0)
	{
		dup2(pipex->fd[0][1], 1);
		clear_all_fds(pipex->fd, pipex->nb_cmd - 1);
	}
	else if (nb_child == pipex->nb_cmd - 1)
	{
		dup2(pipex->fd[nb_child - 1][0], 0);
		clear_all_fds(pipex->fd, pipex->nb_cmd - 1);
	}
	else
	{
		dup2(pipex->fd[nb_child - 1][0], 0);
		dup2(pipex->fd[nb_child][1], 1);
		clear_all_fds(pipex->fd, pipex->nb_cmd - 1);
	}
}

int	waiting(t_pipex *pipex, int nb_child)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	clear_all_fds(pipex->fd, pipex->nb_cmd - 1);
	while (i < nb_child)
		waitpid(pipex->pid[i++], &status, 0);
	free(pipex->pid);
	free(pipex);
	if (WIFEXITED(status) != 0)
		return (WEXITSTATUS(status));
	return (0); // ?
}
