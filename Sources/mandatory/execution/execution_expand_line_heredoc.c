/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_expand_line_heredoc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:13:29 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/21 10:32:25 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

char	*expand_var_heredoc(t_shell *shell, t_filling_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (heredoc->line[i] != '\0')
	{
		if (heredoc->line[i] == '$' && heredoc->line[i + 1] != '\0'
			&& heredoc->line[i + 1] != '$')
		{
			if (expanding_line(shell, heredoc, &i) == 0)
				return (NULL);
			if (heredoc->line == NULL)
				return (NULL);
		}
		i++;
	}
	return (heredoc->line);
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

int	create_new_line(t_filling_heredoc *heredoc, int *i, int j)
{
	char	*new_line;
	char	*tmp;
	int		len;

	len = ft_strlen(heredoc->line) - j + *i + ft_strlen(heredoc->expanded_var);
	new_line = malloc(sizeof(char) * (len + 1));
	if (new_line == NULL)
		return (0);
	ft_strlcpy(new_line, heredoc->line, *i + 1);
	tmp = ft_strjoin(new_line, heredoc->expanded_var);
	free(new_line);
	if (tmp == NULL)
		return (0);
	new_line = ft_strjoin(tmp, heredoc->line + j);
	free(tmp);
	if (new_line == NULL)
		return (0);
	free(heredoc->line);
	heredoc->line = new_line;
	*i = *i + ft_strlen(heredoc->expanded_var) - 1;
	return (1);
}
