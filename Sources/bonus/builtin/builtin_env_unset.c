/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:25:59 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 18:56:20 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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

	i = 1;
	arg = table->args;
	if (arg[1] != NULL && arg[1][0] == '-' && arg[1][1] != '\0')
	{
		write(2, "unset: ", 7);
		write(2, arg[1], 2);
		write(2, ": invalid option\n", 17);
		return (2);
	}
	while (arg[i] != NULL)
	{
		ft_unset_list(exec_struct->shell->env, arg[i]);
		ft_unset_list(exec_struct->export_list, arg[i]);
		i++;
	}
	return (0);
}

/**
 * Unsets the environment variable from the list that is given.
 * Nothing happens if the name was not found.
 * @param list The list in which we will unset.
 * @param name The name we are willing to unset.
*/
void	ft_unset_list(t_env_list **list, char *name)
{
	t_env_list	*tmp;
	t_env_list	*new_next;

	if (list == NULL || *list == NULL || (*list)->name == NULL)
		return ;
	tmp = *list;
	if (ft_strcmp(tmp->name, name) == 0)
	{
		*list = (*list)->next;
		free(tmp->name);
		return (free(tmp->value), free(tmp));
	}
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->name, name) == 0)
		{
			new_next = tmp->next->next;
			free(tmp->next->name);
			free(tmp->next->value);
			free(tmp->next);
			tmp->next = new_next;
			return ;
		}
		tmp = tmp->next;
	}
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
	if (arg[1] != NULL && arg[1][0] == '-' && arg[1][1] != '\0')
	{
		write(2, "env: ", 5);
		write(2, arg[1], 2);
		write(2, ": invalid option\n", 17);
		return (125);
	}
	else if (arg[1] != NULL)
	{
		write(2, "env: Too many arguments\n", 24);
		return (125);
	}
	print_list(*(exec_struct->shell->env), 0);
	return (0);
}

/**
 * Searches for the value of the given name variable. If the name was found, 
 * the value is returned (should NOT be freed after that). If the name was not 
 * found, NULL is returned.
 * @param var_name The name we are searching.
 * @param env The enironment variable list in which we are searching.
*/
char	*ft_getenv(char *var_name, t_env_list **env)
{
	t_env_list	*tmp;

	if (env == NULL || *env == NULL)
		return (NULL);
	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
