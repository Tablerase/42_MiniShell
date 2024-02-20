/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:47:51 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:47:57 by abourgeo         ###   ########.fr       */
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
