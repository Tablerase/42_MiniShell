/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:00:43 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/09 17:55:47 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	lexer_error(t_token *head, char *message)
{
	perror(RED);
	perror("Lexer error: ");
	perror(RESET);
	perror(message);
	free_tokens(head);
	exit(EXIT_FAILURE);
}
