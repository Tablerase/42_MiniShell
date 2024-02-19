/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:57:19 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 14:27:41 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
			|| ft_isalnum(name[i]) == 0 || name[i] == '_')
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
		write(2, "export: `-': not a valid identifier", 35); // verif msg
		return (1);
	}
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

	par = 0;
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

	tmp = *list;
	if (ft_strcmp(tmp->name, name) == 0)
	{
		*list = (*list)->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return ;
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
