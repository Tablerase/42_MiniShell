/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 14:17:33 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

char *get_heredoc_path(t_shell *shell)
{
	t_heredocs *tmp;

	tmp = shell->heredocs;
	while (tmp->next)
		tmp = tmp->next;
	printf("heredoc_path: %s\n", tmp->heredoc_path);
	return (tmp->heredoc_path);
}

/**
 * @brief Append an argument to the command arguments array
 * (array of strings NULL-terminated)
 * @param cmd The command
 * @param arg The argument to append
 * @note This function will append an argument to the command arguments array
 * also expand the variables from dollar tokens and dquote tokens
 */
void	parse_word_and_quotes(t_token *token, t_table *cmd, t_shell *shell)
{
	if (token->type == word)
		cmd_arg_append(shell, cmd, token->value, false);
	else if (token->type == quote)
		cmd_arg_append(shell, cmd, token->value, false);
	else if (token->type == dollar)
		cmd_arg_append(shell, cmd, token->value, dollar);
	else if (token->type == dquote)
		cmd_arg_append(shell, cmd, token->value, dquote);
}

/**
 * @brief Parse the tokens
 * @param lexic: Token list
 * @param shell: Shell structure
 * @note This function will parse the tokens and create the commands table
 */
void	parser(
	t_lexer *lexic,
	t_shell *shell
)
{
	t_token	*tmp;
	t_table	*cmd;

	tmp = lexic->head;
	cmd = cmd_add(&shell->table_head);
	while (tmp != NULL)
	{
		if (tmp->type == pipe_token)
		{
			cmd = cmd_add(&shell->table_head);
		}
		else if (tmp->type == greater)
		{
			tmp = tmp->next;
			cmd_outfile(cmd, outf_file, tmp->value);
		}
		else if (tmp->type == dgreater)
		{
			tmp = tmp->next;
			cmd_outfile(cmd, outf_append, tmp->value);
		}
		else if (tmp->type == less)
		{
			tmp = tmp->next;
			cmd_infile(cmd, shell, inf_file, tmp->value);
		}
		else if (tmp->type == dless)
		{
			tmp = tmp->next;
			if (tmp->type == word)
				create_heredoc(shell, tmp->value, true);
			else
				create_heredoc(shell, tmp->value, false);
			cmd_infile(cmd, shell, inf_heredoc, NULL);
		}
		else
		{
			parse_word_and_quotes(tmp, cmd, shell);
		}
		tmp = tmp->next;
	}
}
