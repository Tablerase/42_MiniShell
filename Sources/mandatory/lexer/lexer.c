/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:22:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 15:07:34 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	init_lexer(t_lexer *syntax)
{
	syntax->head = NULL;
}

void	lexer(char *input, t_lexer *syntax)
{
	init_lexer(syntax);
	lexer_rinput(syntax, input);

	print_tokens(syntax->head);
	free_tokens(syntax->head);
}
