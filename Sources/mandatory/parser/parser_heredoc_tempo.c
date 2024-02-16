/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:04:03 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/16 14:18:32 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

// TODO: heredoc gestion - The below functions are temporary

void	ft_free_here_docs(t_shell *shell)
{
	t_heredocs	*tmp;
	t_heredocs	*next;

	tmp = shell->heredocs;
	while (tmp)
	{
		next = tmp->next;
		unlink(tmp->heredoc_path);
		free(tmp->heredoc_path);
		free(tmp);
		tmp = next;
	}
	shell->heredocs = NULL;
}

static void ft_here_doc_add(t_shell *shell, char *filename_path)
{
	t_heredocs	*new;
	t_heredocs	*tmp;

	new = malloc(sizeof(t_heredocs));
	if (!new)
	{
		ft_putstr_fd("Error: malloc failed\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	new->heredoc_path = filename_path;
	new->next = NULL;
	if (!shell->heredocs)
	{
		shell->heredocs = new;
		return ;
	}
	tmp = shell->heredocs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// TODO: heredoc gestion
static void	ft_here_doc_loop(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		write(1, HBLU, ft_strlen(HBLU));
		write(1, "📬 ", 6);
		write(1, "➜ ", 5);
		write(1, RESET, ft_strlen(RESET));
		line = get_next_line(0, 0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			write(1, "📪\n", 6);
			get_next_line(0, 1);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

// ! File Name assignation will have to be changed
// ! and signal handling will have to be added
/**
 * * Here_doc
 * @return 0 on success, 1 on failure
 * @note Write the heredoc in a file called "here_doc"
*/
int	ft_here_doc_temporaire(t_shell *shell, t_token *word)
{
	int		fd;
	char	*filename;

	filename = "here_doc";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Couldn't create here_doc\n", 2);
		return (EXIT_FAILURE);
	}
	ft_here_doc_loop(word->value, fd);
	ft_here_doc_add(shell, filename);
	return (EXIT_SUCCESS);
}
