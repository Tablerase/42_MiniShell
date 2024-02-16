/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:01:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/16 19:47:58 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * @brief Check if the variable is valid
 * @param str The string to check
 * @param env_var The environment variable string to search
 * @return true if the variable is valid, false otherwise
*/
static bool	var_is_valid(char *str, char *env_var)
{
	int		i;

	i = 0;
	while (str[i] && env_var[i])
	{
		if (str[i] != env_var[i])
		{
			return (false);
		}
		i++;
	}
	if (env_var[i] == '=')
		return (true);
	return (false);
}

/**
 * @brief Expand the variable
 * @param str The string to expand
 * @param env The environment variables
 * @return The expanded string or an empty string if the variable is not found
*/
char *expand_var(char *str, char **env)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		if (var_is_valid(str, env[i]) == true)
		{
			while (env[i][j] != '=')
				j++;
			var = ft_strdup((env[i] + j + 1));
			if (!var)
				return (NULL);
			return (var);
		}
		i++;
	}
	var = ft_strdup("");
	if (!var)
		return (NULL);
	return (var);
}
