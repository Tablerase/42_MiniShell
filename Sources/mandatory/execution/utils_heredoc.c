/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:48:48 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 10:58:51 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	ft_free_filling_heredoc(t_filling_heredoc *heredoc)
{
	if (heredoc->line != NULL)
		free(heredoc->line);
	if (heredoc->var_name != NULL)
		free(heredoc->var_name);
	if (heredoc->fd != -1)
		close(heredoc->fd);
}

void	initialize_filling_heredoc(t_filling_heredoc *heredoc)
{
	heredoc->line = NULL;
	heredoc->filename = NULL;
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	heredoc->expand = 1;
	heredoc->fd = -1;
}

int	expand_exit_code_var_heredoc(t_shell *shell, t_filling_heredoc *heredoc,
		int *i, int j)
{
	j++;
	heredoc->var_name = ft_substr(heredoc->line, *i + 1, j - *i - 1);
	if (heredoc->var_name == NULL)
		return (0);
	heredoc->expanded_var = ft_itoa(shell->exit_code);
	if (create_new_line(heredoc, i, j) == 0)
		return (0);
	return (1);
}

int	affect_var_name(t_shell *shell, t_filling_heredoc *heredoc, int *i)
{
	int	j;

	j = *i + 1;
	if (heredoc->line[j] == '?')
		return (expand_exit_code_var_heredoc(shell, heredoc, i, j));
	while (heredoc->line[j] != '\0' && (ft_isalpha(heredoc->line[j]) == 1
			|| (j != *i + 1 && ft_isalnum(heredoc->line[j]) == 1)
			|| heredoc->line[j] == '_'))
		j++;
	if (j == *i + 1 && ft_isalnum(heredoc->line[j]) == 1)
		j++;
	if (j == *i + 1 && heredoc->line[j] == '?')
		j++;
	if (j == *i + 1)
		return (1);
	heredoc->var_name = ft_substr(heredoc->line, *i + 1, j - *i - 1);
	if (heredoc->var_name == NULL)
		return (0);
	heredoc->expanded_var = ft_getenv(heredoc->var_name, shell->env);
	if (heredoc->expanded_var == NULL)
		heredoc->expanded_var = "";
	if (create_new_line(heredoc, i, j) == 0)
		return (0);
	return (1);
}

int	expanding_line(t_shell *shell, t_filling_heredoc *heredoc, int *i)
{
	int	j;
	int	res;

	j = *i + 1;
	res = affect_var_name(shell, heredoc, i);
	if (ft_strcmp(heredoc->var_name, "?") == 0)
	{
		free(heredoc->expanded_var);
		heredoc->expanded_var = NULL;
	}
	free(heredoc->var_name);
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	if (res == 0)
		return (0);
	return (1);
}
