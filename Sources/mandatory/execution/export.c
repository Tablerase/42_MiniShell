/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:43:52 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:25:35 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

/**
 * With no arguments, export will display the list of environment variables
 * even if they have no value.
 * With at least one argument, export can create a new variable or change the
 * value of an existing environment variable.
 * @param exec_struct Contains the export_list and the env_list.
 * @param table Contains the arguments (if any).
*/
int	ft_export(t_exec *exec_struct, t_table *table)
{
	int		i;
	int		status;
	char	**var_expr;

	i = 0;
	status = 0;
	if (table->args[0] == NULL)
		return (print_list(*(exec_struct->export_list), 1), 0);
	if (check_if_option_export(table->args[0]) == 1)
		return (2);
	var_expr = table->args;
	while (var_expr[i] != NULL)
	{
		if (fill_lists(exec_struct, var_expr[i]) == 0)
			status = 1;
		i++;
	}
	return (status);
}

/**
 * Checks if the name of the variable that is about to be exported is accepted
 * by the grammar rules. It then performs the export based on if the variable
 * already exists or not. On success, returns 1. On error, returns 0.
 * @param exec_struct Contains the export_list to know if the variable already
 * exists
 * @param var_expr Contains the argument passed with the export command. It can
 * only be the name, or can also contain the value associated with the name
 * associated via '='.
*/
int	fill_lists(t_exec *exec_struct, char *var_expr)
{
	char	*name;
	char	*value;
	int		sep;

	sep = search_char(var_expr, '=');
	value = NULL;
	if (sep == -1)
		name = ft_strdup(var_expr);
	else
	{
		name = ft_substr(var_expr, 0, sep);
		value = ft_substr(var_expr, sep + 1, ft_strlen(var_expr));
	}
	if (check_name(name, value) == 0)
		return (0);
	if (name_exists(exec_struct, name, value, sep) == 1)
		return (1);
	if (add_new_var(exec_struct, name, value, sep) == 0)
		return (0);
	return (1);
}

/**
 * Export a new variable into the export list (and the env_list if a value 
 * was given for this name).
 * @param exec_struct Contains the export_list and the env_list.
 * @param name The name of the new variable.
 * @param value The value (if specified, else NULL) related to the name.
 * @param sep If it equals -1, it means that the env_list should not be
 * updated (because no value was given).
*/
int	add_new_var(t_exec *exec_struct, char *name, char *value, int sep)
{
	char	*new_name;
	char	*new_value;

	if (add_node(exec_struct->export_list, name, value) == 0)
	{
		if (value != NULL)
			free(value);
		return (free(name), 0);
	}
	if (sep != -1)
	{
		new_name = ft_strdup(name);
		if (new_name == NULL)
			return (0);
		new_value = ft_strdup(value);
		if (new_value == NULL)
			return (free(new_name), 0);
		if (add_node(exec_struct->env_list, new_name, new_value) == 0)
		{
			free(new_value);
			return (free(new_name), 0);
		}
	}
	return (1);
}

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
				if (add_node(exec_struct->env_list, name, new_value) == 0)
					return (free(name), free(new_value), 1);
			}
			else
				change_list_value(exec_struct->env_list, name, new_value);
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * Change the value in the env_list because the name was already present in the
 * env_list (means that a non-null value has already been given for this name).
 * @param list The env_list that will be updated.
 * @param name The name of the environment variable about to be updated.
 * @param value The updated value that will now be associated with name.
*/
void	change_list_value(t_env_list **list, char *name, char *value)
{
	t_env_list	*tmp;
	char		*tmp_value;

	tmp = *list;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			tmp_value = tmp->value;
			tmp->value = value;
			free(tmp_value);
			free(name);
			return ;
		}
		tmp = tmp->next;
	}
}
