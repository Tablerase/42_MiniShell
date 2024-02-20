/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 20:49:00 by rcutte           ###   ########.fr       */
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
	if ((*token)->link_with_next == true)
	{
		tmp = get_expanded_values(*token, &str_gathered, shell);
		cmd_arg_append(shell, cmd, str_gathered, word);
		free(str_gathered);
		*token = tmp;
	}
	else if ((*token)->type == dollar || (*token)->type == dquote)
	{
		str_gathered = arg_expand(shell, (*token)->value, (*token)->type);
		if (str_gathered == NULL)
			str_gathered = ft_strdup("");
		cmd_arg_append(shell, cmd, str_gathered, word);
		free(str_gathered);
	}
	else
		cmd_arg_append(shell, cmd, (*token)->value, word);
}

static void	parse_signs(
	t_token **tmp,
	t_table *cmd,
	t_shell *shell,
	char **expanded)
{
	t_token	*tmp_old;

	tmp_old = *tmp;
	if ((*tmp)->next->link_with_next == true)
		(*tmp) = get_expanded_values((*tmp)->next, expanded, shell);
	else
	{
		if ((*tmp)->next->type == dollar || (*tmp)->next->type == dquote)
			(*expanded) = arg_expand(shell, (*tmp)->next->value, (*tmp)->next->type);
		else
			(*expanded) = ft_strdup((*tmp)->next->value);
		(*tmp) = (*tmp)->next;
	}
	if (tmp_old->type == greater)
		cmd_outfile(cmd, outf_file, *expanded);
	else if (tmp_old->type == dgreater)
		cmd_outfile(cmd, outf_append, *expanded);
	else if (tmp_old->type == less)
		cmd_infile(cmd, shell, inf_file, *expanded);
	else if (tmp_old->type == dless)
	{
		if (tmp_old->type == word)
			create_heredoc(shell, *expanded, true);
		else
			create_heredoc(shell, *expanded, false);
		cmd_infile(cmd, shell, inf_heredoc, NULL);
	}
	free(*expanded);
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
		else if (tmp->type == greater || tmp->type == dgreater
			|| tmp->type == less || tmp->type == dless)
		{
			parse_signs(&tmp, cmd, shell, &expanded);
		}
		else
		{
			parse_word_and_quotes(&tmp, cmd, shell);
		}
		tmp = tmp->next;
	}
}
