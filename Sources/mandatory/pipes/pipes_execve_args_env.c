/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execve_args_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:34:02 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:34:20 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
