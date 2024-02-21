/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:02:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 18:56:44 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	print_strs(char **array)
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
		printf("%s%s%s", YELHB, array[i], RESET);
		printf(" ");
		i++;
	}
	printf("\n");
}

static void	print_files(t_inf *infd, t_outf *outfd)
{
	printf("Input files: ");
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
}

void	print_cmds(t_shell shell)
{
	t_table	*tmp;

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
			printf("Command: %s%s%s\n", GRNHB, tmp->args[0], RESET);
			printf("Args: ");
			print_strs(tmp->args);
		}
		else
			printf("NULL\n");
		print_files(tmp->infd_head, tmp->outfd_head);
		printf("\n");
		tmp = tmp->next;
	}
	printf("🗃️ End of commands 🗃️\n");
}
