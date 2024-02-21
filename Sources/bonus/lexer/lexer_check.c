/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:39:50 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 16:56:28 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * @brief Check if a character is a whitespace
 * @param c: Character to check
 * @return bool: True if the character is a whitespace, false otherwise
*/
bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (true);
	return (false);
}

/**
 * @brief Check if a character is a quote
 * @param c: Character to check
 * @return bool: True if the character is a quote, false otherwise
*/
bool	is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	else
		return (false);
}

/**
 * @brief Check if str position is at the end of the string
 * @param str : String position (ex: str + position)
 * @return bool: True if the string position is at the end '\0',false otherwise
*/
bool	is_end_of_str(char *str)
{
	if (*str == '\0' || *str + 1 == '\0')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/**
 * @brief Check if a character is a metacharacter
 * @param c: Character to check
 * @return bool: True if the character is a metacharacter, false otherwise
*/
bool	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '$')
		return (true);
	return (false);
}
