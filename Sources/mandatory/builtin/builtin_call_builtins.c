/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:47:51 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 15:48:39 by abourgeo         ###   ########.fr       */
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

int	exit_or_return(t_exec *exec_struct)
{
	int		nb_cmd;
	t_table	*tmp;

	nb_cmd = 0;
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
	{
		ft_free_all(exec_struct->shell);
		free_exec_struct(*exec_struct);
		exit(exec_struct->shell->exit_code);
	}
	return (exec_struct->shell->exit_code);
}

int	update_pwd_oldpwd(t_exec *exec_struct, char *old_pwd)
{
	char	*new_pwd;

	if (old_pwd != NULL && ft_getenv("OLDPWD", exec_struct->shell->env) != NULL)
	{
		change_list_value(exec_struct->export_list, ft_strdup("OLDPWD"),
			ft_strdup(old_pwd));
		change_list_value(exec_struct->shell->env, ft_strdup("OLDPWD"),
			ft_strdup(old_pwd));
	}
	if (old_pwd != NULL)
		free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL && ft_getenv("PWD", exec_struct->shell->env) != NULL)
	{
		change_list_value(exec_struct->export_list, ft_strdup("PWD"),
			ft_strdup(new_pwd));
		change_list_value(exec_struct->shell->env, ft_strdup("PWD"),
			ft_strdup(new_pwd));
	}
	if (new_pwd != NULL)
		free(new_pwd);
	return (0);
}
