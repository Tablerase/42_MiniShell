/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:22:10 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 12:31:12 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static char	*expand_dquote(char *arg, t_shell *shell)
{
	char	*result;
	char	*expanded;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = NULL;
	tmp = NULL;
	result = ft_strdup("");
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
		{
			j = 1;
			if (arg[i + j] == '?')
			{
				expanded = ft_itoa(shell->exit_code);
				tmp = result;
				result = ft_strjoin(result, expanded);
				free(tmp);
				free(expanded);
				i += 2;
			}
			else
			{
				while (arg[i + j] != '\0' && is_whitespace(arg[i + j]) == false)
					j++;
				if (j > 1)
				{
					tmp = ft_substr(arg, i + 1, j - 1);
					expanded = ft_getenv(tmp, shell->env);
					if (expanded == NULL)
						expanded = ft_strdup("");
					else
						expanded = ft_strdup(expanded);
					free(tmp);
					tmp = result;
					result = ft_strjoin(result, expanded);
					free(tmp);
					free(expanded);
				}
				else
				{
					tmp = result;
					result = ft_strjoin(result, "$");
					free(tmp);
				}
				i += j;
				continue;
			}
		}
		else
		{
			expanded = ft_substr(arg, i, 1);
			tmp = result;
			result = ft_strjoin(result, expanded);
			free(tmp);
			free(expanded);
		}
		i++;
	}
	return (result);
}

static char	*arg_expand(t_shell *shell, char *arg, e_token type)
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
 * @param cmd The command
 * @param arg The argument to append
 */
void	cmd_arg_append(t_shell *shell, t_table *cmd, char *arg, e_token type)
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
