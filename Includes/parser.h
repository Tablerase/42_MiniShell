/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/16 14:16:58 by rcutte           ###   ########.fr       */
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
t_table	*cmd_add(t_table **head);

// Files

void	cmd_infile(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path);

// Heredocs

int		ft_here_doc_temporaire(t_shell *shell, t_token *token);
void	ft_free_here_docs(t_shell *shell);

// Debug

void	print_cmds(t_shell shell);

#endif