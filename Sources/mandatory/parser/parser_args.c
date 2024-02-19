/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:22:10 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/19 16:52:55 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static char	*cmd_arg_expand(t_shell *shell, char *arg)
{
	char	*expanded;

	expanded = ft_getenv(arg, shell->env);
	if (expanded == NULL)
		expanded = ft_strdup("");
	else
		expanded = ft_strdup(expanded);
	return (expanded);
}

/**
 * @brief Append an argument to the command arguments array
 * (array of strings NULL-terminated)
 * @param cmd The command
 * @param arg The argument to append
 */
void	cmd_arg_append(t_shell *shell, t_table *cmd, char *arg, bool expand)
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
	if (expand == true)
		tmp[count] = cmd_arg_expand(shell, arg);
	else
		tmp[count] = ft_strdup(arg);
	tmp[count + 1] = NULL;
	cmd->args = tmp;
}
