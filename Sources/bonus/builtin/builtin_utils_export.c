/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:27:25 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:28:07 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Checks if the name given is already an environment variable and performs 
 * the export if it is the case.
 * @param exec_struct Contains the export_list and the env_list.
 * @param name The name of the environment variable.
 * @param value The value (if specified, else NULL) of the environment 
 * variable.
 * @param sep If it equals -1, env_list should not be updated.
*/
int	name_exists(t_exec *exec_struct, char *name, char *value, int sep)
{
	t_env_list	*tmp;
	char		*new_value;

	tmp = *(exec_struct->export_list);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (sep == -1)
				return (free(name), 1);
			new_value = ft_strdup(value);
			if (tmp->value == NULL)
			{
				if (add_node(exec_struct->shell->env, name, new_value) == 0)
					return (free(name), free(new_value), 1);
			}
			else
				change_list_value(exec_struct->shell->env, name, new_value);
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * Checks the name of the environment variable before exporting it.
 * On success, returns 1. On error, returns 0.
 * @param name The name that is being checked on.
 * @param value The value associated with the anme in case it needs to be freed
*/
int	check_name(char *name, char *value)
{
	int	i;

	i = 0;
	if (name == NULL)
	{
		free(name);
		free(value);
		return (0);
	}
	while (name[i] != '\0')
	{
		if ((i == 0 && ft_isalpha(name[i]) == 0)
			|| (i != 0 && ft_isalnum(name[i]) == 0) || name[i] == '_')
		{
			write(2, "export: `", 9);
			write(2, name, ft_strlen(name));
			write(2, "': not a valid identifier\n", 26);
			free(name);
			free(value);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * Check if an option was set with an export call. If it is the case, 
 * 1 is returned. Else 0 is returned.
 * @param arg The argument being checked on.
*/
int	check_if_option_export(char *arg)
{
	if (arg[0] == '-' && arg[1] != '\0')
	{
		write(2, "export: ", 8);
		write(2, arg, 2);
		write(2, ": invalid option\n", 17);
		return (1);
	}
	if (arg[0] == '-' && arg[1] == '\0')
	{
		write(2, "export: `-': not a valid identifier", 35);
		return (1);
	}
	return (0);
}
