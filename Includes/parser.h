/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 19:07:48 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum
{
	inf_file,
	inf_heredoc
} e_infile;

void	parser(t_lexer *lexic, t_shell *shell);

// Nodes

t_table	*new_cmd(void);
void	cmd_add(t_table **head, t_table *new);

// Files

void	cmd_infile(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path);

// Debug

void	print_cmds(t_table *head);

#endif