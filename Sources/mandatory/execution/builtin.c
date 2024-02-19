/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:33:22 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:25:41 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

/**
 * Change the current director. Returns 1 on success, 0 on failure.
 * @param exec_struct The structure containing the shell and the command table.
*/
int	ft_cd(t_exec *exec_struct, t_table *table)
{
	char	*path;

	path = table->args[0]; // can args = NULL ?
	if (path == NULL)
		path = ft_getenv("HOME", exec_struct->env_list);
	if (path == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (path[0] == '-')
	{
		write(2, "cd: ", 4);
		write(2, path, 2);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	if (table->args[1] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (chdir(path) == -1)
		return (perror("cd"), 1); // should we display path like real cd error ?
	return (0);
}

/**
 * Echos the arguments given separated by a white space.
 * If the -n option appears in the first position then no new line
 * will be displayed.
 * @param table Contains the options and the arguments (if any).
*/
int	ft_echo(t_table *table)
{
	int		i;
	char	*str;
	int		no_new_line;

	if (table->args[0] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	no_new_line = ft_echo_option(table->args);
	i = no_new_line;
	while (table->args[i] != NULL)
	{
		if (i != no_new_line)
			write(1, " ", 1);
		str = table->args[i];
		write(1, str, ft_strlen(str));
		i++;
	}
	if (no_new_line == 0)
		write(1, "\n", 1);
	return (0);
}

/**
 * PWD stands for Print Working Directory. On success, returns 0 and
 * displays the PWD. On error, returns a non-null integer and 
 * displays a message.
 * @param table Contains the options and arguments (if any).
*/
int	ft_pwd(t_table *table)
{
	char	*current_path;
	char	**arg;

	arg = table->args;
	if (arg[0] != NULL && arg[0][0] == '-' && arg[0][1] != '\0')
	{
		write(2, "pwd: ", 5);
		write(2, arg[0], 2);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		return (perror("pwd"), 1);
	write(1, current_path, ft_strlen(current_path));
	write(1, "\n", 1);
	free(current_path);
	return (0);
}

/**
 * Display the environment variables that are declared AND 
 * initialized. On success, returns 0. On error, returns a non-null integer.
 * @param exec_struct Contains the list of environment variables of our program.
 * @param table Contains the arguments (if any).
*/
int	ft_env(t_exec *exec_struct, t_table *table)
{
	char	**arg;

	arg = table->args;
	if (arg[0] != NULL && arg[0][0] == '-' && arg[0][1] != '\0')
	{
		write(2, "env: ", 5);
		write(2, arg[0], 2);
		write(2, ": invalid option\n", 17);
		return (125);
	}
	else if (arg[0] != NULL)
	{
		write(2, "env: Too many arguments\n", 24);
		return (125);
	}
	print_list(*(exec_struct->env_list), 0);
	return (0);
}

/**
 * Removes an environment variable if it has been declared and not yet unseted.
 * On success, returns 0. On error, returns a non-null integer.
 * @param exec_struct Contains the env list (only initialized variables)
 * and the export list (both declared and initialized variables).
 * @param table The arguments naming variables that need to be unseted.
*/
int	ft_unset(t_exec *exec_struct, t_table *table)
{
	char	**arg;
	int		i;

	i = 0;
	arg = table->args;
	if (arg[0] != NULL && arg[0][0] == '-' && arg[0][1] != '\0')
	{
		write(2, "unset: ", 7);
		write(2, arg[0], 2);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	while (arg[i] != NULL)
	{
		ft_unset_list(exec_struct->env_list, arg[i]);
		ft_unset_list(exec_struct->export_list, arg[i]);
		i++;
	}
	return (0);
}
