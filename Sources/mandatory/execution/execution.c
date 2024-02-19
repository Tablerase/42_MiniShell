/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:21:03 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 20:41:42 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Checks if the command given by the user is a builtin. On success returns 1.
 * On error, returns 0.
 * @param cmd The command we are checking on.
*/
int	is_builtin(char *cmd)
{
	if (ft_strcmp(CD, cmd) == 0)
		return (1);
	if (ft_strcmp(PWD, cmd) == 0)
		return (1);
	if (ft_strcmp(EXPORT, cmd) == 0)
		return (1);
	if (ft_strcmp(UNSET, cmd) == 0)
		return (1);
	if (ft_strcmp(FT_ECHO, cmd) == 0)
		return (1);
	if (ft_strcmp(EXIT, cmd) == 0)
		return (1);
	if (ft_strcmp(ENV, cmd) == 0)
		return (1);
	return (0);
}

/**
 * Calls the corresponding builtin based on the command.
 * @param exec_struct The data of our program that is needed in our builtins.
 * @param table The datas associated with the current command we are executing.
*/
int	builtin_execution(t_exec *exec_struct, t_table *table)
{
	if (ft_strcmp(CD, table->cmd) == 0)
		return (ft_cd(exec_struct, table));
	else if (ft_strcmp(PWD, table->cmd) == 0)
		return (ft_pwd(table));
	else if (ft_strcmp(EXPORT, table->cmd) == 0)
		return (ft_export(exec_struct, table));
	else if (ft_strcmp(UNSET, table->cmd) == 0)
		return (ft_unset(exec_struct, table));
	else if (ft_strcmp(FT_ECHO, table->cmd) == 0)
		return (ft_echo(table));
	else if (ft_strcmp(EXIT, table->cmd) == 0)
		return (ft_exit(exec_struct, table));
	else
		return (ft_env(exec_struct, table));
	return (0);
}

/**
 * When we have a single command (no pipe), we will directly call a builtin
 * if one is called. Else we create a child process to execute the command.
 * In both cases we keep the exit code to update our variable "?". If an error 
 * occured the command is not executed.
 * @param exec_struct The data of our program.
*/
void	exec_single_cmd(t_exec *exec_struct)
{
	int	status;
	int	pid;

	status = 0;
	if (exec_struct->shell->table_head->cmd == NULL)
	{
		status = redirections(exec_struct->shell, exec_struct->shell->table_head);
		exec_struct->exit_status = status;
		return ;
	}
	else if (is_builtin(exec_struct->shell->table_head->cmd) == 1)
	{
		status = redirections(exec_struct->shell, exec_struct->shell->table_head);
		if (status == 1)
		{
			if (ft_strcmp(EXIT, exec_struct->shell->table_head->cmd) == 1)
				write(2, "exit\n", 5);
			status = builtin_execution(exec_struct, exec_struct->shell->table_head);
		}
		exec_struct->exit_status = status;
		return ;
	}
	else if (exec_struct->shell->table_head->cmd != NULL
		&& exec_struct->shell->table_head->cmd[0] != '\0')
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exec_struct->exit_status = errno;
			return ;
		}
		if (pid == 0)
			single_process(exec_struct, exec_struct->shell->table_head);
		waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status) == 1)
		exec_struct->exit_status = WEXITSTATUS(status);
	// else if (WIFSIGNALED(status) == 1)
	// 	exec_struct->exit_status = 128 + g_signal;
	else
		exec_struct->exit_status = 0;
}

/**
 * Based on the input, execute a single command or a pipeline.
 * @param exec_struct The data of our program.
*/
void	starting_execution(t_exec *exec_struct)
{
	int		nb_cmd;
	t_table	*tmp;

	nb_cmd = 0;
	if (exec_struct->shell->table_head == NULL)
		return ;
	tmp = exec_struct->shell->table_head;
	while (tmp != NULL)
	{
		if (tmp->args != NULL && tmp->args[0] != NULL)
			tmp->cmd = tmp->args[0];
		else
			tmp->cmd = "";
		tmp = tmp->next;
		nb_cmd++;
	}
	if (nb_cmd == 1)
		exec_single_cmd(exec_struct);
	else
		exec_multiple_cmds(exec_struct, nb_cmd);
}

// before (or in) starting_execution(), check
// for empty line or empty cmd (for ex just "")
// check for shell NULL
// isatty before readline (possible when reading for heredoc)
// handle echo $?
// protect write ?
// When error malloc error etc, should we redispay prompt or exit program ?