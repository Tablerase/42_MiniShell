/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:34:24 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 19:08:45 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	lexer_rinput(t_lexer *syntax, char *input)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (input[i] == '|')
		{
			add_last_token(syntax, "|", pipe_token);
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_last_token(syntax, ">>", dgreater);
				if (input[i + 2] == '>')
					lexer_error(syntax->head, "near unexpected token `>>>'");
				i += 2;
			}
			else
			{
				add_last_token(syntax, ">", greater);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				if (input[i + 2] == '<')
					lexer_error(syntax->head, "near unexpected token `<<<'");
				add_last_token(syntax, "<<", dless);
				i += 2;
			}
			else
			{
				add_last_token(syntax, "<", less);
				i++;
			}
		}
		else if (input[i] == '$')
		{
			j = i;
			while (input[j] && is_whitespace(input[j]) == false
				&& is_metachar(input[j]) == false)
				j++;
			tmp = ft_substr(input, i, j - i);
			add_last_token(syntax, tmp, dollar);
			i = j;
		}
		else if (input[i] == '\'')
		{
			j = i + 1;
			if (is_end_of_str(input + j) == true)
			{
				lexer_error(syntax->head, "unclosed quotes");
			}
			while (input[j] && input[j] != '\'')
			{
				j++;
				if (input[j] == '\0')
					lexer_error(syntax->head, "unclosed quotes");
			}
			tmp = ft_substr(input, i + 1, j - i - 1);
			add_last_token(syntax, tmp, quote);
			i = j + 1;
		}
		else if (input[i] == '\"')
		{
			j = i + 1;
			if (is_end_of_str(input + j) == true)
			{
				lexer_error(syntax->head, "unclosed quotes");
			}
			while (input[j] && input[j] != '\"')
			{
				j++;
				if (input[j] == '\0')
					lexer_error(syntax->head, "unclosed quotes");
			}
			tmp = ft_substr(input, i + 1, j - i - 1);
			add_last_token(syntax, tmp, dquote);
			i = j + 1;
		}
		else
		{
			j = i;
			while (input[j] && is_whitespace(input[j]) == false
				&& is_quotes(input[j]) == false
				&& is_metachar(input[j]) == false)
			{
				j++;
			}
			tmp = ft_substr(input, i, j - i);
			add_last_token(syntax, tmp, word);
			i = j;
		}
	}
}
