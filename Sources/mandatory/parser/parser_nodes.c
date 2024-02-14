/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:17 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/14 15:30:45 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_table *new_cmd(void)
{
	t_table	*cmd;

	cmd = malloc(sizeof(t_table));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infd_head = NULL;
	cmd->outfd_head = NULL;
	cmd->next = NULL;
	return (cmd);
}
