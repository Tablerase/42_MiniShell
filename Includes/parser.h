/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/19 18:13:45 by rcutte           ###   ########.fr       */
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

typedef enum
{
	outf_file,
	outf_append
} e_outfile;

void	parser(t_lexer *lexic, t_shell *shell);

// Nodes

t_table	*new_cmd(void);
t_table	*cmd_add(t_table **head);

// Args

// char	*expand_var(char *arg, char **env);
void	cmd_arg_append(t_shell *shell, t_table *cmd, char *arg, e_token type);

// Files

void	cmd_infile(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path);
void	cmd_outfile(t_table *cmd, e_outfile type, char *filename_path);

// Heredocs

int		ft_here_doc_temporaire(t_shell *shell, t_token *token);
void	ft_free_here_docs(t_shell *shell);

// Debug

void	print_cmds(t_shell shell);

#endif