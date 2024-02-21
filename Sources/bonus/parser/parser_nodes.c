/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:17 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 19:45:44 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Create a new command structure
 * @return The new command
 */
t_table	*new_cmd(void)
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
 * @return new The new empty command at the end of the list
 */
t_table	*cmd_add(t_table **head)
{
	t_table	*tmp;

	if (*head == NULL)
	{
		*head = new_cmd();
		return (*head);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd();
	return (tmp->next);
}
