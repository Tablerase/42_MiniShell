/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:22:02 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/13 17:37:46 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	init_lexer(t_lexer *syntax)
{
	syntax->head = NULL;
}

/**
 * @brief The lexer function
 * @param input The input string
 * @param syntax The lexer structure
 * @return bool: true if the lexer was successful, false otherwise
*/
bool	lexer(char *input, t_lexer *syntax)
{
	bool		ret;

	init_lexer(syntax);
	ret = lexer_rinput(syntax, input);
	if (ret == true)
	{
		ret = lexer_check_order(syntax->head);
		if (ret == true)
		{
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}
