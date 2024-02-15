/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:45:54 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/15 18:48:49 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	ft_free_outfds(t_outf *head)
{
	t_outf	*tmp;
	t_outf	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_infds(t_inf *head)
{
	t_inf	*tmp;
	t_inf	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_cmds(t_table *head)
{
	t_table	*tmp;
	t_table	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->args != NULL)
			ft_free_strs(tmp->args);
		if (tmp->infd_head != NULL)
			ft_free_infds(tmp->infd_head);
		if (tmp->outfd_head != NULL)
			ft_free_outfds(tmp->outfd_head);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_all(t_shell *shell)
{
	ft_free_strs(shell->env);
	if (shell->table_head != NULL)
		ft_free_cmds(shell->table_head);
}
