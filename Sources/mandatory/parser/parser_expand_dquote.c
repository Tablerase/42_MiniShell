/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:47:51 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 10:03:45 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static void	putain_de_norme(int *j, char *arg, int**i)
{
	*j = **i + 1;
	while (arg[*j] != '\0' && is_whitespace(arg[*j]) == false
		&& arg[*j] != '$')
		(*j)++;
	*j = *j - **i;
}

static void	exp_dquote_dol_loop_2(
	t_shell *shell,
	char *arg,
	char ***result,
	int **i
)
{
	char	*tmp;
	char	*expanded;
	int		j;

	putain_de_norme(&j, arg, i);
	if (j > 1)
	{
		tmp = ft_substr(arg, *(*i) + 1, j - 1);
		expanded = ft_getenv(tmp, shell->env);
		if (expanded == NULL)
			expanded = ft_strdup("");
		else
			expanded = ft_strdup(expanded);
		free(tmp);
		tmp = *(*result);
		*(*result) = ft_strjoin(*(*result), expanded);
		free(expanded);
	}
	else
	{
		tmp = *(*result);
		*(*result) = ft_strjoin(*(*result), "$");
	}
	free(tmp);
	*(*i) += j;
}

static void	exp_dquote_dol_loop(
	t_shell *shell,
	char *arg,
	char **result,
	int *i
)
{
	char	*expanded;
	char	*tmp;
	int		j;

	j = 1;
	if (arg[*i + j] == '?')
	{
		expanded = ft_itoa(shell->exit_code);
		tmp = *result;
		*result = ft_strjoin(*result, expanded);
		free(tmp);
		free(expanded);
		*i += 2;
	}
	else
	{
		exp_dquote_dol_loop_2(shell, arg, &result, &i);
	}
}

char	*expand_dquote(char *arg, t_shell *shell)
{
	char	*result;
	char	*expanded;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = NULL;
	result = ft_strdup("");
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
			exp_dquote_dol_loop(shell, arg, &result, &i);
		else
		{
			expanded = ft_substr(arg, i, 1);
			tmp = result;
			result = ft_strjoin(result, expanded);
			free(tmp);
			free(expanded);
			i++;
		}
	}
	return (result);
}
