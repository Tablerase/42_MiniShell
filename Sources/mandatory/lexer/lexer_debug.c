/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 17:00:01 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	print_tokens_type(t_token token_unit)
{
	if (token_unit.type == pipe_token)
		printf("Type: pipe_token\n");
	else if (token_unit.type == greater)
		printf("Type: greater\n");
	else if (token_unit.type == dgreater)
		printf("Type: dgreater\n");
	else if (token_unit.type == less)
		printf("Type: less\n");
	else if (token_unit.type == dless)
		printf("Type: dless\n");
	else if (token_unit.type == dollar)
		printf("Type: dollar\n");
	else if (token_unit.type == quote)
		printf("Type: quote\n");
	else if (token_unit.type == dquote)
		printf("Type: dquote\n");
	else if (token_unit.type == word)
		printf("Type: word\n");
}

void	print_tokens(t_token *tokens)
{
	printf("\n🔗 List of tokens: 🔗\n\n");
	while (tokens)
	{
		// printf("Token: %s\n", tokens->value);
		print_tokens_type(*tokens);
		printf("⏬\n");
		tokens = tokens->next;
	}
}
