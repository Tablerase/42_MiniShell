/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:22:10 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 07:08:46 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * @brief Expand the dollar and double quote tokens
 * @param shell The shell
 * @param arg The argument to expand
 * @param type The type of the token (dollar or dquote)
 * @return The expanded argument (or an empty string if the variable is not set)
*/
char	*arg_expand(t_shell *shell, char *arg, enum e_token type)
{
	char	*expanded;

	if (type == dollar)
	{
		if (arg[0] == '?')
			return (ft_itoa(shell->exit_code));
		else
			expanded = ft_getenv(arg, shell->env);
		if (expanded == NULL)
			return (ft_strdup(""));
		return (ft_strdup(expanded));
	}
	else
	{
		expanded = expand_dquote(arg, shell);
		if (expanded == NULL)
			return (ft_strdup(""));
	}
	return (expanded);
}

/**
 * @brief Append an argument to the command arguments array
 * (array of strings NULL-terminated)
 * @param shell The shell (to get the environment variables)
 * @param cmd The command
 * @param arg The argument to append
 * @param type The type of the token (dollar or dquote or word)
 * @note This function will append an argument to the command arguments array
 * (the argument that is passed as a param is strduped to avoid any issues with
 * the memory management of the argument passed as a param)
 */
void	cmd_arg_append(
			t_shell *shell,
			t_table *cmd,
			char *arg,
			enum e_token type)
{
	char	**tmp;
	int		count;
	int		i;

	count = ft_strs_len(cmd->args);
	tmp = malloc(sizeof(char *) * (count + 2));
	if (!tmp)
		return ;
	if (count > 0)
	{
		i = 0;
		while (cmd->args[i])
		{
			tmp[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		ft_free_strs(cmd->args);
	}
	if (type == dollar || type == dquote)
		tmp[count] = arg_expand(shell, arg, type);
	else
		tmp[count] = ft_strdup(arg);
	tmp[count + 1] = NULL;
	cmd->args = tmp;
}
