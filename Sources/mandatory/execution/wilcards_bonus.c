/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcards_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:11:15 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 14:27:54 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

char	**wilcard_expansion(char *expression);
char	**create_args_wildcards(char *expression);
char	*matches_wildcard(char *name, char *expression);
int		number_matches_wildcard(char *expression);

/**
 * This function should be called when a valid wilcard is found.
 * It will return a tab containing the names that matches the given expression.
 * If no matches were found, it will return NULL which means that the 
 * expression should remain unvhanged in the input.
 * @param expression The expression that needs a wilcard expansion.
*/
char	**wilcard_expansion(char *expression)
{
	int				i;
	DIR				*stream;
	char			*new_name;
	char			**new_args;
	struct dirent	*current_object;

	i = 0;
	new_args = create_args_wildcards(expression);
	if (new_args == NULL)
		return (NULL);
	stream = opendir("./");
	if (stream == NULL)
		return (NULL);
	current_object = readdir(stream);
	while (current_object != NULL)
	{
		new_name = matches_wildcard(current_object->d_name, expression);
		if (new_name != NULL)
			new_args[i++] = new_name;
		current_object = readdir(stream);
	}
	new_args[i] = NULL;
	closedir(stream);
	return (new_args);
}

/**
 * Based on the numbr of matching names, it will allocate the tab that will 
 * contain all the matching names (strings). If no match were found, NULL 
 * is returned.
 * @param expression The expression that needs a wilcard expansion.
*/
char	**create_args_wildcards(char *expression)
{
	int		len;
	char	**new_args;

	len = number_matches_wildcard(expression);
	if (len == 0)
		return (NULL);
	new_args = malloc((len + 1) * sizeof(char *));
	if (new_args == NULL)
		return (NULL);
	return (new_args);
}

/**
 * Checks if the given name matches the expression (using wilcard expansion).
 * If it matches, the name (newly allocated) is returned. Else NULL is returned.
 * @param name The name we are checking on.
 * @param expression The expression that needs a wilcard expansion.
*/
char	*matches_wildcard(char *name, char *expression)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (expression[i] != '\0')
	{
		if (expression[i] == '*')
		{
			while (expression[i] == '*')
				i++;
			while (name[j] != '\0' && expression[i] != name[j])
				j++;
		}
		if (expression[i] != name[j] || expression[i] == '\0')
			break ;
		i++;
		j++;
	}
	if (expression[i] == name[j] && name[j] == '\0'
		&& ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
		return (ft_strdup(name));
	return (NULL);
}

/**
 * Counts and returns the number of matching names.
 * @param expression The expression that needs a wilcard expansion.
*/
int	number_matches_wildcard(char *expression)
{
	int				len;
	char			*name;
	DIR				*stream;
	struct dirent	*current_object;

	len = 0;
	stream = opendir("./");
	current_object = readdir(stream);
	while (current_object != NULL)
	{
		name = matches_wildcard(current_object->d_name, expression);
		if (name != NULL)
		{
			len++;
			free(name);
		}
		current_object = readdir(stream);
	}
	closedir(stream);
	return (len);
}

// int	main(void)
// {
// 	int		i;
// 	char	**args;
// 	char	*expression;

// 	i = 0;
// 	expression = ft_strdup("a*");
// 	args = wilcard_expansion(expression);
// 	if (args == NULL)
// 		printf("%s\n", expression);
// 	else
// 	{
// 		while (args[i] != NULL)
// 		{
// 			printf("%s\n", args[i]);
// 			free(args[i++]);
// 		}
// 		free(args);
// 	}
// 	free(expression);
// 	return (0);
// }
