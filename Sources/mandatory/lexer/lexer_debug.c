/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:11:16 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/09 15:51:45 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void print_tokens_type(t_token tokens)
{
	if (tokens.type == pipe_token)
		printf("Type: pipe_token\n");
	else if (tokens.type == greater)
		printf("Type: greater\n");
	else if (tokens.type == dgreater)
		printf("Type: dgreater\n");
	else if (tokens.type == less)
		printf("Type: less\n");
	else if (tokens.type == dless)
		printf("Type: dless\n");
	else if (tokens.type == dollar)
		printf("Type: dollar\n");
	else if (tokens.type == quote)
		printf("Type: quote\n");
	else if (tokens.type == dquote)
		printf("Type: dquote\n");
	else if (tokens.type == word)
		printf("Type: word\n");
}

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("\n🔗 List of tokens: 🔗\n\n");
	while (tokens)
	{
		printf("Token: %s\n", tokens->value);
		print_tokens_type(*tokens);
		printf("⏬\n");
		tokens = tokens->next;
	}
}
