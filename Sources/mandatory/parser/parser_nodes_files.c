/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:33:43 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 19:23:00 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Init the input file list of the command
 * @param cmd The command
 * @param shell The shell
 * @param type The type of the input file (inf_file or inf_heredoc)
 * @param filename_path The path of the input file
*/
static void cmd_infile_init(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path)
{
	t_heredocs	*tmp;

	cmd->infd_head = malloc(sizeof(t_inf));
	if (!cmd->infd_head)
		return ;
	cmd->infd_head->next = NULL;
	if (type == inf_heredoc)
	{
		tmp = shell->heredocs;
		while (tmp->next)
			tmp = tmp->next;
		cmd->infd_head->file = ft_strdup(tmp->heredoc_path);
		cmd->infd_head->heredoc = true;
	}
	else
	{
		cmd->infd_head->file = ft_strdup(filename_path);
		cmd->infd_head->heredoc = false;
	}
}

/**
 * @brief Add an input file to the command input file list
 * @param cmd The command
 * @param shell The shell
 * @param type The type of the input file (inf_file or inf_heredoc)
 * @param filename_path The path of the input file
*/
static void cmd_infile_add(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path
)
{
	t_heredocs 	*tmp;
	t_inf		*tmp_cmd_inf;

	tmp_cmd_inf = cmd->infd_head;
	while (tmp_cmd_inf->next)
		tmp_cmd_inf = tmp_cmd_inf->next;
	tmp_cmd_inf->next = malloc(sizeof(t_inf));
	if (!tmp_cmd_inf->next)
		return ;
	tmp_cmd_inf->next->next = NULL;
	if (type == inf_heredoc)
	{
		tmp = shell->heredocs;
		while (tmp->next)
			tmp = tmp->next;
		cmd->infd_head->file = ft_strdup(tmp->heredoc_path);
		cmd->infd_head->heredoc = true;
	}
	else
	{
		cmd->infd_head->file = ft_strdup(filename_path);
		cmd->infd_head->heredoc = false;
	}
}

void	cmd_infile(t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path)
{
	if (!cmd)
		return ;
	if (cmd->infd_head == NULL)
		cmd_infile_init(cmd, shell, type, filename_path);
	else
		cmd_infile_add(cmd, shell, type, filename_path);
}
