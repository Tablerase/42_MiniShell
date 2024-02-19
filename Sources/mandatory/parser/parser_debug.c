/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:02:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/19 15:42:54 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	print_strs(char **array)
{
	int	i;

	i = 0;
	if (!array)
	{
		printf("NULL\n");
		return ;
	}
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
	printf("\n");
}

void	print_cmds(t_shell shell)
{
	t_table	*tmp;
	t_inf	*infd;
	t_outf	*outfd;

	printf("🗃️ Printing commands 🗃️\n");
	if (!shell.table_head)
	{
		printf("No commands\n");
		return ;
	}
	tmp = shell.table_head;
	while (tmp)
	{
		printf("📜 Command 📜\n");
		if (tmp->args)
		{
			printf("Command: %s\n", tmp->args[0]);
			printf("Args: ");
			print_strs(tmp->args);
		}
		else
			printf("NULL\n");
		printf("Input files: ");
		infd = tmp->infd_head;
		while (infd != NULL)
		{
			printf("%s", infd->file);
			if (infd->heredoc == true)
				printf("(heredoc) ");
			else
				printf(" ");
			infd = infd->next;
		}
		printf("\n");
		printf("Output files: ");
		outfd = tmp->outfd_head;
		while (outfd)
		{
			printf("%s", outfd->file);
			if (outfd->append == true)
				printf("(append) ");
			else
				printf(" ");
			outfd = outfd->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
}
