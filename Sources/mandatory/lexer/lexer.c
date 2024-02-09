/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:22:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/09 17:59:57 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

t_token	*lexer(char *input)
{
	t_token	*head;

	head = NULL;
	lexer_rinput(head, input);
	printf("test\n");
	print_tokens(head);
	return (head);
}
