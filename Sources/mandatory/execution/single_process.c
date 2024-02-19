/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:52:12 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 20:08:23 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * If a single command was called (and is not a builtin) we will then 
 * execute this function which is supposed to create arguements needed by 
 * execve. On succes, exits with 0. On error, exits with a non-zero error code.
 * @param exec_struct The data of our program.
 * @param table The data generated by the input.
*/
int	single_process(t_exec *exec_struct, t_table *table)
{
	char	*path_cmd;
	char	**args_cmd;
	char	**env;
	int		redir;

	redir = redirections(exec_struct->shell, table);
	if (redir == 0 || is_a_directory(table->cmd) == 1)
	{
		free_process(*exec_struct, NULL, NULL, NULL);
		exit(1 + (125 * redir));
	}
	path_cmd = find_path(exec_struct->env_list, table->cmd);
	if (path_cmd == NULL)
	{
		write(2, table->cmd, ft_strlen(table->cmd));
		write(2, ": Command not found\n", 20);
		free_process(*exec_struct, path_cmd, NULL, NULL);
		exit(127);
	}
	args_cmd = get_args_cmd(table->args);
	env = copy_env(exec_struct->env_list);
	free_process(*exec_struct, NULL, NULL, NULL);
	execve(path_cmd, args_cmd, env);
	return (execve_fail(path_cmd, args_cmd, env));
}

/**
 * Generates the env variable according to the environment variables 
 * of our minishell. If an error occured, returns NULL.
 * @param env_list The list of our environment variables.
*/
char	**copy_env(t_env_list **env_list)
{
	int			len;
	char		**env;
	t_env_list	*tmp;

	env = malloc((size_list(env_list) + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	len = 0;
	if (env_list != NULL)
	{
		tmp = *env_list;
		while (tmp != NULL)
		{
			env[len++] = get_env_line(tmp);
			if (env[len - 1] == NULL)
				return (free_tabtab(env), NULL);
			tmp = tmp->next;
		}
		free(tmp);
	}
	env[len] = NULL;
	return (env);
}

/**
 * Creates a string according to the environment variable that is passed 
 * as argument. If an error occured, NULL is returned.
 * @param line Contains the name and the value of an environment variable.
*/
char	*get_env_line(t_env_list *line)
{
	char	*env_line;
	char	*tmp;

	tmp = ft_strjoin(line->name, "=");
	if (tmp == NULL)
		return (NULL);
	if (line->value == NULL)
		env_line = ft_strdup(tmp);
	else
		env_line = ft_strjoin(tmp, line->value);
	free(tmp);
	if (env_line == NULL)
		return (NULL);
	return (env_line);
}

/**
 * Generates the argv variable needed for the execve call. If an error occures 
 * NULL is returned.
 * @param cmd The command that will have the first position in argv
 * @param args The arguments that will fill the remain strings of argv.
*/
char	**get_args_cmd(char **args)
{
	int		len;
	char	**argv;

	len = 0;
	while (args != NULL && args[len] != NULL)
		len++;
	argv = malloc((len + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	len = 0;
	while (args != NULL && args[len] != NULL)
	{
		argv[len] = ft_strdup(args[len]);
		if (argv[len] == NULL)
			return (free_tabtab(argv), NULL);
		len++;
	}
	argv[len] = NULL;
	return (argv);
}

/**
 * Clears the data and returns the right error message and code if execve 
 * failed.
 * @param path_cmd A pointer that needs to be freed
 * @param args_cmd A pointer that needs to be freed
 * @param env A pointer that needs to be freed
*/
int	execve_fail(char *path_cmd, char **args_cmd, char **env)
{
	perror(path_cmd);
	free(path_cmd);
	free_tabtab(args_cmd);
	free_tabtab(env);
	exit(errno);
}
