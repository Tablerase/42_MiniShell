/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 19:51:25 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * @brief Append an argument to the command arguments array
 * (array of strings NULL-terminated)
 * @param cmd The command
 * @param arg The argument to append
 * @note This function will append an argument to the command arguments array
 * also expand the variables from dollar tokens and dquote tokens
 */
static void	parse_word_and_quotes(t_token **token, t_table *cmd, t_shell *shell)
{
	char	*str_gathered;
	t_token	*tmp;

	str_gathered = NULL;
	tmp = get_expanded_values(*token, &str_gathered, shell);
	cmd_arg_append(shell, cmd, str_gathered, word);
	*token = tmp;
	free(str_gathered);
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
	char	*expanded;

	expanded = NULL;
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
			tmp = get_expanded_values(tmp->next, &expanded, shell);
			cmd_outfile(cmd, outf_file, expanded);
			free(expanded);
		}
		else if (tmp->type == dgreater)
		{
			tmp = get_expanded_values(tmp->next, &expanded, shell);
			cmd_outfile(cmd, outf_append, expanded);
			free(expanded);
		}
		else if (tmp->type == less)
		{
			tmp = get_expanded_values(tmp->next, &expanded, shell);
			cmd_infile(cmd, shell, inf_file, expanded);
			free(expanded);
		}
		else if (tmp->type == dless)
		{
			tmp = get_expanded_values(tmp->next, &expanded, shell);
			if (tmp->type == word)
				create_heredoc(shell, tmp->value, true);
			else
				create_heredoc(shell, tmp->value, false);
			cmd_infile(cmd, shell, inf_heredoc, NULL);
			free(expanded);
			if (g_signal == SIGINT)
				return ;
		}
		else
		{
			parse_word_and_quotes(&tmp, cmd, shell);
		}
		tmp = tmp->next;
	}
}
