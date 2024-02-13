/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:33:55 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 16:32:30 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Create a new token
 * @param value: Token value
 * @param type: Token type
 * @return t_token*: New token
*/
t_token	*new_token(char *value, e_token type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

/**
 * @brief Add a token to the end of the list
 * @param head: Token list
 * @param value: Token value
 * @param type: Token type
*/
void	add_last_token(t_lexer *syntax, char *value, e_token type)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(value, type);
	if (!new)
		return ;
	if (!syntax->head)
	{
		syntax->head = new;
	}
	else
	{
		tmp = syntax->head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/**
 * @brief Free the token list
 * @param tokens: Token list head
*/
void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->type == word || tokens->type == quote
			|| tokens->type == dquote || tokens->type == dollar)
		{
			if (tokens->value != NULL)
				free(tokens->value);
		}
		free(tokens);
		tokens = tmp;
	}
}