/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:10 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 18:49:21 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

int	filename(t_shell *shell, t_filling_heredoc *heredoc)
{
	char	*old_name;

	old_name = NULL;
	heredoc->filename = ft_strdup("heredoc");
	if (heredoc->filename == NULL)
		return (0);
	while (access(heredoc->filename, F_OK) == 0)
	{
		old_name = heredoc->filename;
		heredoc->filename = ft_strjoin(old_name, "_");
		free(old_name);
		if (heredoc->filename == NULL)
			return (0);
	}
	heredoc->fd = open(heredoc->filename, O_CREAT | O_WRONLY, 0644);
	if (heredoc->fd == -1)
		return (perror("heredoc"), 0);
	return (add_heredoc_filename(shell, heredoc->filename));
}

int	add_heredoc_filename(t_shell *shell, char *name)
{
	t_heredocs	*tmp;

	if (shell->heredocs == NULL)
	{
		shell->heredocs = malloc(sizeof(t_heredocs));
		if (shell->heredocs == NULL)
			return (0);
		shell->heredocs->heredoc_path = name;
		shell->heredocs->next = NULL;
		return (1);
	}
	tmp = shell->heredocs;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_heredocs));
	if (tmp->next == NULL)
		return (0);
	tmp->next->heredoc_path = name;
	tmp->next->next = NULL;
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

char	*expand_var_heredoc(t_env_list **env_list, t_filling_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (heredoc->line[i] != '\0')
	{
		if (heredoc->line[i] == '$' && heredoc->line[i + 1] != '\0')
		{
			if (expanding_line(env_list, heredoc, &i) == 0)
				return (NULL);
			if (heredoc->line == NULL)
				return (NULL);
		}
		i++;
	}
	return (heredoc->line);
}

int	create_heredoc(t_shell *shell, char *lim, bool expand)
{
	t_filling_heredoc	heredoc;

	initialize_filling_heredoc(&heredoc);
	if (filename(shell, &heredoc) == 0)
		return (0);
	while (1)
	{
		free(heredoc.line);
		heredoc.line = NULL;
		heredoc.line = readline("> ");
		if (heredoc.line == NULL || ft_strcmp(heredoc.line, lim) == 0)
			break ;
		if (expand == 1)
			heredoc.line = expand_var_heredoc(shell->env, &heredoc);
		if (heredoc.line == NULL)
			break ;
		write(heredoc.fd, heredoc.line, ft_strlen(heredoc.line));
		write(heredoc.fd, "\n", 1);
	}
	ft_free_filling_heredoc(&heredoc);
	return (1);
}
