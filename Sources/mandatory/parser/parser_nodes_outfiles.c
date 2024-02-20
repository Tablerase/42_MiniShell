/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes_outfiles.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:09:03 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 18:49:14 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Init the output file list of the command
 * @param cmd The command
 * @param type The type of the output file (outf_file or inf_heredoc)
 * @param filename_path The path of the output file
*/
static void	cmd_outfile_init(
	t_table *cmd,
	e_outfile type,
	char *filename_path)
{
	cmd->outfd_head = malloc(sizeof(t_inf));
	if (!cmd->outfd_head)
		return ;
	cmd->outfd_head->next = NULL;
	cmd->outfd_head->file = ft_strdup(filename_path);
	if (type == outf_append)
	{
		cmd->outfd_head->append = true;
	}
	else
	{
		cmd->outfd_head->append = false;
	}
}

/**
 * @brief Add an output file to the command output file list
 * @param cmd The command
 * @param shell The shell
 * @param type The type of the output file (outf_file or outf_append)
 * @param filename_path The path of the output file
*/
static void	cmd_outfile_add(
	t_table *cmd,
	e_outfile type,
	char *filename_path)
{
	t_outf		*tmp_out;

	tmp_out = cmd->outfd_head;
	while (tmp_out->next)
		tmp_out = tmp_out->next;
	tmp_out->next = malloc(sizeof(t_outf));
	tmp_out = tmp_out->next;
	if (!tmp_out)
		return ;
	tmp_out->next = NULL;
	tmp_out->file = ft_strdup(filename_path);
	if (type == outf_append)
	{
		tmp_out->append = true;
	}
	else
	{
		tmp_out->append = false;
	}
}

/**
 * @brief Add an output file to the command output file list
 * @param cmd The command
 * @param shell The shell
 * @param type The type of the output file (outf_file or outf_append)
 * @param filename_path The path of the output file
*/
void	cmd_outfile(t_table *cmd, e_outfile type, char *filename_path)
{
	if (!cmd)
		return ;
	if (cmd->outfd_head == NULL)
		cmd_outfile_init(cmd, type, filename_path);
	else
		cmd_outfile_add(cmd, type, filename_path);
}
