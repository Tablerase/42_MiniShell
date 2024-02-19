/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:10 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 14:27:32 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

typedef struct s_filling_heredoc
{
	int		fd;
	int		expand;
	char	*line;
	char	*limiter;
	char	*filename;
	char	*var_name;
	char	*expanded_var;
}	t_filling_heredoc;

void	initialize(t_filling_heredoc *heredoc)
{
	heredoc->line = NULL;
	heredoc->limiter = NULL;
	heredoc->filename = NULL;
	heredoc->var_name = NULL;
	heredoc->expanded_var = NULL;
	heredoc->expand = 1;
	heredoc->fd = -1;
}

int	filename(t_filling_heredoc *heredoc)
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
	return (1);
}

char	*create_heredoc(char *limiter)
{
	t_filling_heredoc	heredoc;

	initialize(&heredoc);
	if (filename(&heredoc))
}

int	main(int argc, char *argv[])
{

	if (argc == 2)
	{
		create_heredoc(argv[1]);
	}
}

// parsing maison pas ouf :)
// unlink every heredoc file
// every quote is deleted from the limiter, even if it's not a pair...
