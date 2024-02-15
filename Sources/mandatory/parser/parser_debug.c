/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:02:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 19:24:28 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	print_cmds(t_table *head)
{
	t_table	*tmp;
	t_inf	*infd;
	// t_outf	*outfd;

	printf("🗃️ Printing commands 🗃️\n");
	tmp = head;
	while (tmp)
	{
		printf("📜 Command 📜\n");
		// printf("Command: %s\n", tmp->cmd);
		// printf("Args: ");
		// if (tmp->args)
		// 	ft_print_strs(tmp->args);
		// else
		// 	printf("NULL\n");
		printf("Input files: ");
		infd = tmp->infd_head;
		while (infd)
		{
			printf("%s ", infd->file);
			infd = infd->next;
		}
		printf("\n");
		// printf("Output files: ");
		// outfd = tmp->outfd_head;
		// while (outfd)
		// {
		// 	printf("%s ", outfd->file);
		// 	outfd = outfd->next;
		// }
		// printf("\n");
		tmp = tmp->next;
	}
}
