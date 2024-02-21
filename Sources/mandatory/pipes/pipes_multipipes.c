/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_multipipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:37:50 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 08:10:40 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	exec_multiple_cmds(t_exec *exec_struct, int nb_cmd, char *input)
{
	int		i;
	t_pipex	*pipex;
	t_table	*table_cmd;

	pipex = init_pipex(exec_struct, nb_cmd);
	if (pipex == NULL)
		return (perror("Initialization of pipex"));
	i = 0;
	table_cmd = exec_struct->shell->table_head;
	while (table_cmd != NULL)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			exec_struct->shell->exit_code = waiting(pipex, i);
			return (perror("fork"));
		}
		if (pipex->pid[i] == 0)
			start_child_process(pipex, table_cmd, i, input);
		table_cmd = table_cmd->next;
		i++;
	}
	signal(SIGINT, &sig_handler_non_interactive);
	signal(SIGQUIT, &sig_handler_non_interactive);
	exec_struct->shell->exit_code = waiting(pipex, i);
}

void	start_child_process(t_pipex *pipex, t_table *table_cmd,
		int nb_child, char *input)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	free(input);
	pipex->nb_child = nb_child;
	redirect_into_pipes(pipex, nb_child);
	if (redirections(table_cmd) == 0)
		exit_child_process(pipex, 1);
	if (is_a_directory(table_cmd->cmd) == 1)
		exit_child_process(pipex, 126);
	if (is_builtin(table_cmd->cmd) == 1)
		builtin_in_pipe(pipex, table_cmd);
	command_in_pipe(pipex, table_cmd);
}

int	**create_pipex_fd(int *pid, int nb_cmd)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc((nb_cmd - 1) * sizeof(int *));
	if (fd == NULL)
		return (perror("malloc"), NULL);
	while (i < nb_cmd - 1)
	{
		fd[i++] = malloc(2 * sizeof(int));
		if (fd[i - 1] == NULL)
			return (error_mallocing_fd(pid, fd, i), NULL);
	}
	return (fd);
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
	if (WIFSIGNALED(status) != 0)
		return (status + g_signal);
	return (0);
}
