/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/16 16:42:41 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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
		// else if (tmp->type == dless)
		// {
		// 	tmp = tmp->next;
		// 	// TODO: heredoc gestion
		// 	ft_here_doc_temporaire(shell, tmp);
		// 	cmd_infile(cmd, shell, inf_heredoc, "here_doc");
		// }
		// else
		// {
		// 	add_arg(&shell->table_head, &tmp);
		// }
		tmp = tmp->next;
	}
}
