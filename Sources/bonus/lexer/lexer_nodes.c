/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:33:55 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 07:03:54 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Create a new token
 * @param value: Token value
 * @param type: Token type
 * @param link_with_next: Link the token with the next one
 * (when no space between)
 * @return t_token*: New token
*/
t_token	*new_token(char *value, enum e_token type, bool link_with_next)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->link_with_next = link_with_next;
	return (token);
}

/**
 * @brief Add a token to the end of the list
 * @param head: Token list
 * @param value: Token value
 * @param type: Token type
 * @param link_with_next: Link the token with the next one
*/
void	add_last_token(
	t_lexer *syntax,
	char *value,
	enum e_token type,
	bool link_with_next)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(value, type, link_with_next);
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
