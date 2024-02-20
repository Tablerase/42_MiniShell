/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:10:57 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/20 17:12:28 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

int	create_heredoc(t_shell *shell, char *lim, bool expand)
{
	t_filling_heredoc	heredoc;

	init_filling_heredoc(&heredoc);
	if (filename(shell, &heredoc) == 0)
		return (0);
	heredoc.fd = open(heredoc.filename, O_CREAT | O_WRONLY, 0644);
	if (heredoc.fd == -1)
		return (perror("heredoc"), 0);
	while (1)
	{
		free(heredoc.line);
		heredoc.line = NULL;
		heredoc.line = readline("> ");
		if (heredoc.line == NULL || ft_strcmp(heredoc.line, lim) == 0)
			break ;
		if (expand == 1)
			heredoc.line = expand_var_heredoc(shell, &heredoc);
		if (heredoc.line == NULL)
			break ;
		write(heredoc.fd, heredoc.line, ft_strlen(heredoc.line));
		write(heredoc.fd, "\n", 1);
	}
	ft_free_filling_heredoc(&heredoc);
	return (1);
}

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

void	ft_free_here_docs(t_shell *shell)
{
	t_heredocs	*tmp;
	t_heredocs	*next;

	tmp = shell->heredocs;
	while (tmp != NULL)
	{
		next = tmp->next;
		unlink(tmp->heredoc_path);
		free(tmp->heredoc_path);
		free(tmp);
		tmp = next;
	}
	shell->heredocs = NULL;
}

void	ft_free_filling_heredoc(t_filling_heredoc *heredoc)
{
	if (heredoc->line != NULL)
		free(heredoc->line);
	if (heredoc->var_name != NULL)
		free(heredoc->var_name);
	if (heredoc->fd != -1)
		close(heredoc->fd);
}
