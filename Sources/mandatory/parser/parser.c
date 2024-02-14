/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/14 15:43:44 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

// TODO: heredoc gestion

static ft_here_doc_temporaire(t_shell *shell, t_token **tmp)
{
	// TODO: if `Ctrl+C` interrupt, parsing stop and but input saved in history

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

	tmp = lexic->head;
	while (tmp != NULL)
	{
		if (tmp->type == pipe_token)
		{
			add_cmd(&shell->table_head, &tmp);
		}
		else if (tmp->type == greater)
		{
			add_outfd(&shell->table_head, &tmp);
		}
		else if (tmp->type == dgreater)
		{
			add_outfd(&shell->table_head, &tmp);
		}
		else if (tmp->type == less)
		{
			add_infd(&shell->table_head, &tmp);
		}
		else if (tmp->type == dless)
		{
			// TODO: heredoc gestion
			ft_here_doc(&shell->heredocs, &tmp);
			add_infd(&shell->table_head, &tmp);
		}
		else
		{
			add_arg(&shell->table_head, &tmp);
		}
}
