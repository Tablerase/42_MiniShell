/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:34:24 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/09 18:02:54 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	lexer_rinput(t_token *head, char *input)
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
			add_last_token(head, "|", pipe_token);
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_last_token(head, ">>", dgreater);
				i += 2;
			}
			else
			{
				add_last_token(head, ">", greater);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_last_token(head, "<<", dless);
				i += 2;
			}
			else
			{
				add_last_token(head, "<", less);
				i++;
			}
		}
		else if (input[i] == '$')
		{
			j = i;
			while (input[j] && is_whitespace(input[j]) == false)
				j++;
			tmp = ft_substr(input, i, j - i);
			add_last_token(head, tmp, dollar);
			free(tmp);
			i = j;
		}
		else if (input[i] == '\'')
		{
			j = i + 1;
			while (input[j] && input[j] != '\'')
				j++;
			tmp = ft_substr(input, i + 1, j - i - 1);
			add_last_token(head, tmp, quote);
			free(tmp);
			i = j + 1;
		}
		else if (input[i] == '\"')
		{
			j = i + 1;
			while (input[j] && input[j] != '\"')
				j++;
			tmp = ft_substr(input, i + 1, j - i - 1);
			add_last_token(head, tmp, dquote);
			free(tmp);
			i = j + 1;
		}
		else
		{
			j = i;
			print_tokens(head);
			printf("input[i] = %c\n", input[i]);
			while (input[j] && input[j] != ' ')
				j++;
			tmp = ft_substr(input, i, j - i);
			add_last_token(head, tmp, word);
			free(tmp);
			i = j;
		}
	}
	print_tokens(head);
}
