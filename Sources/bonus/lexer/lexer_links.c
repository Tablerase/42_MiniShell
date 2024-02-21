/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:42:58 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 18:07:46 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/**
 * @brief Check if a character is linkable
 * @param c The character to check
 * @return bool: true if the character is linkable, false otherwise
 * @note A character is linkable if it is not a whitespace allow to gather
 * multiple words together to form a single argument in the command
*/
bool	is_linkable(char c)
{
	if (!c)
		return (false);
	if (c == '\0')
		return (false);
	if (is_whitespace(c) == true)
		return (false);
	return (true);
}
