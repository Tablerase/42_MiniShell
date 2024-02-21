/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 07:07:54 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_infile
{
	inf_file,
	inf_heredoc
};

enum e_outfile
{
	outf_file,
	outf_append
};

void	parser(t_lexer *lexic, t_shell *shell);

// Nodes

t_table	*new_cmd(void);
t_table	*cmd_add(t_table **head);

// Expansions of $variables

char	*expand_dquote(char *arg, t_shell *shell);
char	*arg_expand(t_shell *shell, char *arg, enum e_token type);
t_token	*get_expanded_values(
			t_token *token,
			char **str_gathered,
			t_shell *shell);

// Args

void	cmd_arg_append(
			t_shell *shell,
			t_table *cmd,
			char *arg,
			enum e_token type);

// Files

void	cmd_infile(
			t_table *cmd,
			t_shell *shell,
			enum e_infile type,
			char *filename_path);
void	cmd_outfile(t_table *cmd, enum e_outfile type, char *filename_path);

// Debug

void	print_cmds(t_shell shell);

#endif