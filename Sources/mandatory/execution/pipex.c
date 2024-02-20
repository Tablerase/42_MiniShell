/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:38:49 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 10:24:55 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
	fd = malloc((nb_cmd - 1) * sizeof(int *));
	if (fd == NULL)
		return (perror("malloc"), NULL);
	while (i < nb_cmd - 1)
	{
		fd[i++] = malloc(2 * sizeof(int));
		if (fd[i - 1] == NULL)
			return (NULL); // clear it
	}
	i = 0;
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

int	builtin_in_pipe(t_pipex *pipex, t_table *table_cmd)
{
	int	status;

	status = builtin_execution(pipex->exec_struct, table_cmd);
	exit_child_process(pipex, -1);
	exit(status);
}

int	command_in_pipe(t_pipex *pipex, t_table *table)
{
	char	*path_cmd;
	char	**args_cmd;
	char	**env;

	path_cmd = find_path(pipex->exec_struct->shell->env, table->cmd);
	if (path_cmd == NULL)
	{
		write(2, table->cmd, ft_strlen(table->cmd));
		write(2, ": Command not found\n", 20);
		exit_child_process(pipex, 127);
	}
	args_cmd = get_args_cmd(table->args);
	env = copy_env(pipex->exec_struct->shell->env);
	exit_child_process(pipex, -1);
	execve(path_cmd, args_cmd, env);
	perror(path_cmd);
	free(path_cmd);
	free_tabtab(args_cmd);
	free_tabtab(env);
	exit(errno);
}

void	start_child_process(t_pipex *pipex, t_table *table_cmd, int nb_child)
{
	signal(SIGINT, SIG_DFL);
	pipex->nb_child = nb_child;
	redirect_into_pipes(pipex, nb_child);
	if (redirections(pipex->exec_struct->shell, table_cmd) == 0)
		exit_child_process(pipex, 1);
	if (is_a_directory(table_cmd->cmd) == 1)
		exit_child_process(pipex, 126);
	if (is_builtin(table_cmd->cmd) == 1)
		builtin_in_pipe(pipex, table_cmd);
	command_in_pipe(pipex, table_cmd);
}

void	exec_multiple_cmds(t_exec *exec_struct, int nb_cmd)
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
			perror("fork");
			return ;
		}
		if (pipex->pid[i] == 0)
			start_child_process(pipex, table_cmd, i);
		table_cmd = table_cmd->next;
		i++;
	}
	signal(SIGINT, &sig_handler_non_interactive);
	exec_struct->shell->exit_code = waiting(pipex, i);
}
