/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 19:47:10 by rcutte           ###   ########.fr       */
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

// Expansions of $variables

char	*expand_dquote(char *arg, t_shell *shell);
char	*arg_expand(t_shell *shell, char *arg, e_token type);
t_token	*get_expanded_values(
	t_token *token,
	char **str_gathered,
	t_shell *shell);

// Args

void	cmd_arg_append(t_shell *shell, t_table *cmd, char *arg, e_token type);

// Files

void	cmd_infile(
	t_table *cmd,
	t_shell *shell,
	e_infile type,
	char *filename_path);
void	cmd_outfile(t_table *cmd, e_outfile type, char *filename_path);

// Debug

void	print_cmds(t_shell shell);

#endif