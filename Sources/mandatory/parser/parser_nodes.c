/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:17 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 18:55:35 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Create a new command structure
 * @return The new command
 */
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

/**
 * @brief Add a command to the command list
 * @param head The head of the command list
 * @param new The command to add
 */
void	cmd_add(t_table **head, t_table *new)
{
	t_table	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
