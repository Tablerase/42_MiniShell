/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:02:04 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 18:54:29 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	lexer_check_order(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == pipe_token)
		{
			if (!tmp->next || tmp->next->type == pipe_token)
				lexer_error(head, "near unexpected token '|'");
		}
		else if (tmp->type == greater || tmp->type == dgreater
			|| tmp->type == less || tmp->type == dless)
		{
			if (!tmp->next || (tmp->next->type != word
					&& tmp->next->type != quote && tmp->next->type != dquote
					&& tmp->next->type != dollar))
				lexer_error(head, "near unexpected token special character");
		}
		tmp = tmp->next;
	}
}
