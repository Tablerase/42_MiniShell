/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:15:29 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 18:45:51 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * Performs the redirections of std_in and std_out.
 * Once an error is detected, a message is displayed and the redirections stop.
 * In bash once an error is detected, the redirections and file creations 
 * immediatly stop.
 * @param shell Contains the infiles and outfiles (if any).
*/
int	redirections(t_shell *shell, t_table *table)
{
	if (redirect_input(shell, table->infd_head) == 0)
		return (0);
	if (redirect_output(table->outfd_head) == 0)
		return (0);
	return (1);
}

/**
 * Performs the std_in redirections. On success, returns 1. If any error 
 * occured, 0 is returned.
 * @param infile All the std_in redirections of our current command.
*/
int	redirect_input(t_shell *shell, t_inf *infile)
{
	int		i;
	int		fd_infile;
	t_inf	*tmp;

	i = 0;
	tmp = infile;
	while (tmp != NULL)
	{
		if (is_a_directory(tmp->file) == 1)
			return (0);
		fd_infile = open(tmp->file, O_RDONLY, 0644);
		if (fd_infile == -1)
			return (perror(tmp->file), 0);
		if (dup2(fd_infile, 0) == -1)
		{
			close(fd_infile);
			return (perror("dup2"), 0);
		}
		close(fd_infile);
		if (tmp->heredoc == 1)
			if (add_heredocpath(shell->heredocs, tmp->file) == 0)
				return (perror("strdup"), 0);
		tmp = tmp->next;
	}
	return (1);
}

int	add_heredocpath(t_heredocs *heredocs, char *filename)
{
	t_heredocs	*tmp;

	tmp = heredocs;
	if (tmp == NULL)
	{
		tmp = malloc(sizeof(t_heredocs));
		if (tmp == NULL)
			return (0);
		tmp->heredoc_path = filename;
		tmp->next = NULL;
		return (1);
	}
	while (tmp != NULL)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_heredocs));
	if (tmp->next == NULL)
		return (0);
	tmp->next->heredoc_path = filename;
	tmp->next->next = NULL;
	return (1);
}

/**
 * Performs the std_out redirections. On success, returns 1. If any error 
 * occured, 0 is returned.
 * @param infile All the std_out redirections of our current command.
*/
int	redirect_output(t_outf *outfile)
{
	int		i;
	int		fd_out;
	t_outf	*tmp;

	i = 0;
	tmp = outfile;
	while (tmp != NULL)
	{
		if (is_a_directory(tmp->file) == 1)
			return (0);
		if (tmp->append == 0)
			fd_out = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd_out = open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
			return (perror(tmp->file), 0);
		if (dup2(fd_out, 1) == -1)
		{
			close(fd_out);
			return (perror("dup2"), 0);
		}
		close(fd_out);
		tmp = tmp->next;
	}
	return (1);
}

/**
 * Checks if the redirections is performed on a directory. If it is a 
 * directory, returns 1. Else returns 0.
 * @param filename The filename we are checking on.
*/
int	is_a_directory(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		write(2, filename, ft_strlen(filename));
		write(2, ": Is a directory\n", 17);
		return (1);
	}
	return (0);
}
