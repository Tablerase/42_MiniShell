/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:15:29 by abourgeo          #+#    #+#             */
/*   Updated: 2024/02/19 11:25:28 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/exec.h"

/**
 * Performs the redirections of stdin and stdout.
 * Once an error is detected, a message is displayed and the redirections stop.
 * In bash once an error is detected, the redirections and file creations 
 * immediatly stop.
 * @param table Contains the infiles and outfiles (if any).
*/
int	redirections(t_table *table)
{
	if (redirect_input(table->infile) == 0)
		return (0);
	if (redirect_output(table->outfile) == 0)
		return (0);
	return (1);
}

/**
 * Performs the stdin redirections. On success, returns 1. If any error 
 * occured, 0 is returned.
 * @param infile All the stdin redirections of our current command.
*/
int	redirect_input(char **infile)
{
	int	i;
	int	fd_infile;

	i = 0;
	if (infile == NULL)
		return (1);
	while (infile[i] != NULL)
	{
		if (is_a_directory(infile[i]) == 1)
			return (0);
		fd_infile = open(infile[i], O_RDONLY, 0644);
		if (fd_infile == -1)
			return (perror(infile[i]), 0);
		if (dup2(fd_infile, 0) == -1)
		{
			close(fd_infile);
			return (perror("dup2"), 0);
		}
		close(fd_infile);
		i++;
	}
	return (1);
}

/**
 * Performs the stdout redirections. On success, returns 1. If any error 
 * occured, 0 is returned.
 * @param infile All the stdout redirections of our current command.
*/
int	redirect_output(t_outf **outfile)
{
	int	i;
	int	fd_out;

	i = 0;
	if (outfile == NULL)
		return (1);
	while (outfile[i] != NULL)
	{
		if (is_a_directory(outfile[i]->file) == 1)
			return (0);
		if (outfile[i]->append == 0)
			fd_out = open(outfile[i]->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd_out = open(outfile[i]->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
			return (perror(outfile[i]->file), 0);
		if (dup2(fd_out, 1) == -1)
		{
			close(fd_out);
			return (perror("dup2"), 0);
		}
		close(fd_out);
		i++;
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
