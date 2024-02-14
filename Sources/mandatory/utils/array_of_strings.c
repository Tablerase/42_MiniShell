/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_of_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:49:28 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/14 14:18:09 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * @brief Get the length of an array of strings
 * @param array: Array of strings (null-terminated to be safe)
 * @return int: Length of the array, 0 if the array is NULL
 * @note If the array is not null-terminated, the
 * function will do a conditional jump
 */
int	ft_strs_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Free an array of strings
 * @param array: Array of strings
 */
void	ft_free_strs(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Duplicate an array of strings
 * @param array: Array of strings (null-terminated to be safe)
 * @return char**: New array of strings null-terminated, NULL in case of error
 * @note If the array is not null-terminated, the function will do
 * a conditional jump
 */
char	**ft_strs_dup(char **array)
{
	int		i;
	char	**new;

	i = ft_strs_len(array);
	if (i == 0)
		return (NULL);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		if (!new[i])
		{
			ft_free_strs(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}
