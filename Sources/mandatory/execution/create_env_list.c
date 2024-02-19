/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:25 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:25:40 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

/**
 * Filling the list of our environment variables with the env variable 
 * from main. On error, returns NULL. On success, returns the address of 
 * the first environment variable.
 * @param list The first element of our list of variable environment.
 * @param env Our environment variable.
*/
t_env_list	*init_list(t_env_list *list, char **env)
{
	int		i;
	int		sep;
	char	*name;
	char	*value;

	i = 0;
	sep = 0;
	list = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		sep = search_char(env[i], '=');
		name = ft_substr(env[i], 0, sep);
		value = ft_substr(env[i], sep + 1, ft_strlen(env[i]));
		if (name == NULL || value == NULL || add_node(&list, name, value) == 0)
		{
			free(name);
			free(value);
			free_list(&list);
			return (NULL);
		}
		i++;
	}
	return (list);
}

/**
 * Adds a node at the end of the list of environment variables.
 * On success, returns 1. On error, returns 0.
 * @param list the head of the list
 * @param name the name of the environment variable added
 * @param value the value of the environment variable added
*/
int	add_node(t_env_list **list, char *name, char *value)
{
	t_env_list	*tmp;

	if (list == NULL)
		return (0);
	tmp = *list;
	if (tmp == NULL)
	{
		tmp = malloc(sizeof(t_env_list));
		if (tmp == NULL)
			return (0);
		tmp->name = name;
		tmp->value = value;
		tmp->next = NULL;
		*list = tmp;
		return (1);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env_list));
	if (tmp->next == NULL)
		return (0);
	tmp->next->name = name;
	tmp->next->value = value;
	tmp->next->next = NULL;
	return (1);
}

/**
 * Returns the index of the first occurence of c in a string.
 * @param str The string in which we are searching the character
 * @param c The character we search
*/
int	search_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

/**
 * Prints the content of the environment variables with 
 * their content present in our list.
 * @param list The head of our list of environment variable
*/
void	print_list(t_env_list *list, int export)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		if (tmp->value != NULL)
		{
			write(1, "=", 1);
			if (export == 1)
				write(1, "\"", 1);
			write(1, tmp->value, ft_strlen(tmp->value));
			if (export == 1)
				write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}
