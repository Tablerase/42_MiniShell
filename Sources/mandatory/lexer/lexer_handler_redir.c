/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:49:29 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/13 16:08:10 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

e_handler	lexer_handle_space(char *input, int *i)
{
	if (input[*i] == ' ')
	{
		(*i)++;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_pipe(t_lexer *syntax, char *input, int *i)
{
	if (input[*i] == '|')
	{
		add_last_token(syntax, "|", pipe_token);
		(*i)++;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_greater(t_lexer *syntax, char *input, int *i)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_last_token(syntax, ">>", dgreater);
			if (input[*i + 2] == '>')
			{
				lexer_error(syntax->head, "near unexpected token `>>>'");
				return (error);
			}
			(*i) += 2;
		}
		else
		{
			add_last_token(syntax, ">", greater);
			(*i)++;
		}
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_less(t_lexer *syntax, char *input, int *i)
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
			add_last_token(syntax, "<<", dless);
			(*i) += 2;
		}
		else
		{
			add_last_token(syntax, "<", less);
			(*i)++;
		}
		return (found);
	}
	return (not_found);
}
