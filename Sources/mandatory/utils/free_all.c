/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:45:54 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 16:24:27 by abourgeo         ###   ########.fr       */
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
		if (tmp->file != NULL)
			free(tmp->file);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_cmds(t_shell *shell)
{
	t_table	*tmp;
	t_table	*next;

	tmp = shell->table_head;
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
	shell->table_head = NULL;
}

void	ft_free_all(t_shell *shell)
{
	if (shell->env != NULL)
		free_list(shell->env);
	free(shell->env);
	if (shell->table_head != NULL)
		ft_free_cmds(shell);
	close(shell->std_in);
	close(shell->std_out);
	clear_history();
}
