/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_clear_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:41:56 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:43:36 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
	ft_free_all(pipex->exec_struct->shell);
	free(pipex->pid);
	free(pipex);
	if (status >= 0)
		exit(status);
	return (1);
}

void	error_forking(int *pid, int **fd, int i)
{
	{
		while (--i >= 0)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			free(fd[i]);
		}
		free(fd);
		free(pid);
		return ;
	}
	perror("fork");
}

void	error_mallocing_fd(int *pid, int **fd, int i)
{
	{
		while (--i >= 0)
			free(fd[i]);
		free(fd);
		free(pid);
		return ;
	}
	perror("malloc");
}
