/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:46:35 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/13 14:50:39 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

e_handler	lexer_handle_space(char *input, int *i)
{
	if (input[*i] == ' ')
	{
		(*i)++;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_dollar(t_lexer *syntax, char *input, int *i)
{
	int		j;
	char	*tmp;

	if (input[*i] == '$')
	{
		j = *i;
		while (input[j] && is_whitespace(input[j]) == false
			&& is_metachar(input[j]) == false)
			j++;
		tmp = ft_substr(input, *i, j - *i);
		if (!tmp)
			return (lexer_error(syntax->head, "malloc error"), error);
		add_last_token(syntax, tmp, dollar);
		*i = j;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_quote(t_lexer *syntax, char *input, int *i)
{
	int		j;
	char	*tmp;

	if (input[*i] == '\'')
	{
		j = *i + 1;
		if (is_end_of_str(input + j) == true)
		{
			return (lexer_error(syntax->head, "unclosed quotes"), error);
		}
		while (input[j] && input[j] != '\'')
		{
			j++;
			if (input[j] == '\0')
				return (lexer_error(syntax->head, "unclosed quotes"), error);
		}
		tmp = ft_substr(input, *i + 1, j - *i - 1);
		if (!tmp)
			return (lexer_error(syntax->head, "malloc error"), error);
		add_last_token(syntax, tmp, quote);
		*i = j + 1;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_dquote(t_lexer *syntax, char *input, int *i)
{
	int		j;
	char	*tmp;

	if (input[*i] == '\"')
	{
		j = *i + 1;
		if (is_end_of_str(input + j) == true)
		{
			return (lexer_error(syntax->head, "unclosed quotes"), error);
		}
		while (input[j] && input[j] != '\"')
		{
			j++;
			if (input[j] == '\0')
				return (lexer_error(syntax->head, "unclosed quotes"), error);
		}
		tmp = ft_substr(input, *i + 1, j - *i - 1);
		if (!tmp)
			return (lexer_error(syntax->head, "malloc error"), error);
		add_last_token(syntax, tmp, dquote);
		*i = j + 1;
		return (found);
	}
	return (not_found);
}

e_handler	lexer_handle_word(t_lexer *syntax, char *input, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	while (input[j] && is_whitespace(input[j]) == false
		&& is_quotes(input[j]) == false
		&& is_metachar(input[j]) == false)
	{
		j++;
	}
	if (j == *i)
		return (not_found);
	tmp = ft_substr(input, *i, j - *i);
	if (!tmp)
		return (lexer_error(syntax->head, "malloc error"), error);
	add_last_token(syntax, tmp, word);
	*i = j;
	return (found);
}
