/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_cd_echo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:19:25 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 15:43:27 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
	if (arg[1] != NULL && arg[1][0] == '-' && arg[1][1] != '\0')
	{
		write(2, "pwd: ", 5);
		write(2, arg[1], 2);
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

int	ft_error_cd(char *str, int status)
{
	write(2, str, ft_strlen(str));
	return (status);
}

/**
 * Change the current director. Returns 1 on success, 0 on failure.
 * @param exec_struct The structure containing the shell and the command table.
*/
int	ft_cd(t_exec *exec_struct, t_table *table)
{
	char	*path;
	char	*old_pwd;

	path = table->args[1];
	old_pwd = getcwd(NULL, 0);
	if (path == NULL)
		path = ft_getenv("HOME", exec_struct->shell->env);
	if (path == NULL)
		return (ft_error_cd("cd: HOME not set\n", 1));
	if (path[0] == '-')
	{
		write(2, "cd: ", 4);
		write(2, path, 2);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	if (table->args[1] != NULL && table->args[2] != NULL)
		return (ft_error_cd("cd: too many arguments\n", 1));
	if (chdir(path) == -1)
		return (free(old_pwd), perror("cd"), 1);
	return (update_pwd_oldpwd(exec_struct, old_pwd));
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

	if (table->args[1] == NULL)
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
	if (no_new_line == 1)
		write(1, "\n", 1);
	return (0);
}

/**
 * Checks if the -n option is present in first position of an echo call.
 * @param args Arguments of the echo call.
*/
int	ft_echo_option(char **args)
{
	int	i;
	int	par;

	par = 1;
	while (args[par] != NULL)
	{
		i = 1;
		if (args[par][0] != '-')
			break ;
		while (args[par][i] == 'n')
			i++;
		if (args[par][i] != '\0' || i == 1)
			break ;
		par++;
	}
	return (par);
}
