/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_create_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:49:11 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:49:59 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Sorts the export_list which will be printed when the
 * export command is called.
 * @param export_list The list we are sorting.
*/
void	sort_export_list(t_env_list **export_list)
{
	t_env_list	*tmp_list;
	t_env_list	*new_pos;
	t_env_list	*min;
	char		*tmp_val;

	tmp_list = *export_list;
	while (tmp_list != NULL)
	{
		new_pos = tmp_list->next;
		min = tmp_list;
		while (new_pos != NULL)
		{
			if (ft_strcmp(min->name, new_pos->name) > 0)
				min = new_pos;
			new_pos = new_pos->next;
		}
		tmp_val = min->name;
		min->name = tmp_list->name;
		tmp_list->name = tmp_val;
		tmp_val = min->value;
		min->value = tmp_list->value;
		tmp_list->value = tmp_val;
		tmp_list = tmp_list->next;
	}
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
