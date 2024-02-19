/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_not_done.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:10 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:49 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

typedef struct s_heredoc
{
	int		fd;
	int		expand;
	char	*line;
	char	*limiter;
	char	*filename;
	char	*var_name;
	char	*expanded_var;
}	t_heredoc;

void	ft_free(t_heredoc *heredoc)
{
	if (heredoc->line != NULL)
		free(heredoc->line);
	if (heredoc->limiter != NULL)
		free(heredoc->limiter);
	if (heredoc->filename != NULL)
		free(heredoc->filename);
	if (heredoc->var_name != NULL)
		free(heredoc->var_name);
	if (heredoc->fd != -1)
		close(heredoc->fd);
}
// if (heredoc->expanded_var != NULL)
// 	free(heredoc->expanded_var); // not allocated

void	initialize(t_heredoc *heredoc)
{
	heredoc->line = NULL;
	heredoc->limiter = NULL;
	heredoc->filename = NULL;
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	heredoc->expand = 1;
	heredoc->fd = -1;
}

char	*allocate_lim(char *lim)
{
	char	*new_lim;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (lim[i] != '\0')
	{
		if (lim[i] != '\'' && lim[i] != '\"')
			len++;
		i++;
	}
	new_lim = malloc(sizeof(char) * (len + 1));
	if (new_lim == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (lim[i] != '\0')
	{
		if (lim[i] != '\'' && lim[i] != '\"')
			new_lim[len++] = lim[i];
		i++;
	}
	new_lim[len] = '\0';
	return (new_lim);
}

void	update_expand(t_heredoc *heredoc, char *lim)
{
	int	i;
	int	simple_quote;
	int	double_quote;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	while (lim[i] != '\0')
	{
		if (lim[i] == '\'')
			simple_quote++;
		if (lim[i] == '\"')
			double_quote++;
		i++;
	}
	if (simple_quote < 2 && double_quote < 2)
		heredoc->expand = 1;
	else
		heredoc->expand = 0;
	heredoc->limiter = allocate_lim(lim);
}

int	filename(t_heredoc *heredoc)
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
	heredoc->fd = open(heredoc->filename, O_CREAT | O_RDWR, 0644);
	if (heredoc->fd == -1)
		return (0);
	return (1);
}

int	create_new_line(t_heredoc *heredoc, int *i, int j)
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

int	affect_var_name(t_heredoc *heredoc, int *i)
{
	int	j;

	j = *i + 1;
	while (heredoc->line[j] != '\0' && heredoc->line[j] != ' ')
		j++;
	heredoc->var_name = ft_substr(heredoc->line, *i + 1, j - *i - 1);
	if (heredoc->var_name == NULL)
		return (0);
	heredoc->expanded_var = getenv(heredoc->var_name);
	if (heredoc->expanded_var == NULL)
		heredoc->expanded_var = "";
	if (create_new_line(heredoc, i, j) == 0)
		return (0);
	return (1);
}

int	expanding_line(t_heredoc *heredoc, int *i)
{
	int	j;
	int	res;

	j = *i + 1;
	res = affect_var_name(heredoc, i);
	free(heredoc->var_name);
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	if (res == 0)
		return (0);
	return (1);
}

char	*expand_var(t_heredoc *heredoc)
{
	int	i;

	i = 0;
	while (heredoc->line[i] != '\0')
	{
		if (heredoc->line[i] == '$' && heredoc->line[i + 1] != '\0')
		{
			if (expanding_line(heredoc, &i) == 0)
				return (NULL);
			if (heredoc->line == NULL)
				return (NULL);
		}
		i++;
	}
	return (heredoc->line);
}

int	create_heredoc(t_heredoc *heredoc, char *lim)
{
	if (filename(heredoc) == 0)
		return (0);
	update_expand(heredoc, lim);
	if (heredoc->limiter == NULL)
		return (0);
	while (1)
	{
		free(heredoc->line);
		heredoc->line = readline("> ");
		if (heredoc->line == NULL)
			return (ft_free(heredoc), 0);
		if (ft_strcmp(heredoc->line, heredoc->limiter) == 0)
			return (ft_free(heredoc), 1);
		if (heredoc->expand == 1)
			heredoc->line = expand_var(heredoc);
		if (heredoc->line == NULL)
			return (ft_free(heredoc), 0);
		write(heredoc->fd, heredoc->line, ft_strlen(heredoc->line));
		write(heredoc->fd, "\n", 1);
	}
}

int	main(int argc, char *argv[])
{
	t_heredoc	heredoc;
	char		**args;
	int			i;

	if (argc == 2)
	{
		i = 0;
		args = ft_split(argv[1], ' ');
		if (args == NULL)
			return (1);
		while (args[i] != NULL)
		{
			if (ft_strncmp(args[i], "<<", 2) == 0)
			{
				initialize(&heredoc);
				create_heredoc(&heredoc, args[i + 1]);
			}
			i++;
		}
		i = 0;
		while (args[i] != NULL)
			free(args[i++]);
		free(args);
	}
}

// parsing maison pas ouf :)
// unlink every heredoc file
// every quote is deleted from the limiter, even if it's not a pair...
