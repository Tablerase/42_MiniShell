/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:49:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 07:03:29 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

enum e_handler	lexer_handle_space(char *input, int *i)
{
	if (is_whitespace(input[*i]) == true)
	{
		(*i)++;
		return (found);
	}
	return (not_found);
}

enum e_handler	lexer_handle_pipe(t_lexer *syntax, char *input, int *i)
{
	if (input[*i] == '|')
	{
		add_last_token(syntax, "|", pipe_token, false);
		(*i)++;
		return (found);
	}
	return (not_found);
}

enum e_handler	lexer_handle_greater(t_lexer *syntax, char *input, int *i)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_last_token(syntax, ">>", dgreater, false);
			if (input[*i + 2] == '>')
			{
				lexer_error(syntax->head, "near unexpected token `>>>'");
				return (error);
			}
			(*i) += 2;
		}
		else
		{
			add_last_token(syntax, ">", greater, false);
			(*i)++;
		}
		return (found);
	}
	return (not_found);
}

enum e_handler	lexer_handle_less(t_lexer *syntax, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			if (input[*i + 2] == '<')
			{
				lexer_error(syntax->head, "near unexpected token `<<<'");
				return (error);
			}
			add_last_token(syntax, "<<", dless, false);
			(*i) += 2;
		}
		else
		{
			add_last_token(syntax, "<", less, false);
			(*i)++;
		}
		return (found);
	}
	return (not_found);
}
