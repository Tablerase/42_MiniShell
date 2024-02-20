/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:02:14 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 20:48:10 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

// inside of get_expanded_values loop
static void	get_exp_val_inside_loop(
	t_shell *shell,
	t_token **tmp,
	char **expanded,
	char **str_gathered)
{
	char	*tmp_old;

	tmp_old = *str_gathered;
	if ((*tmp)->next->type == dollar || (*tmp)->next->type == dquote)
	{
		*expanded = arg_expand(shell, (*tmp)->next->value, (*tmp)->next->type);
		*str_gathered = ft_strjoin(*str_gathered, *expanded);
		free(*expanded);
	}
	else
		*str_gathered = ft_strjoin(*str_gathered, (*tmp)->next->value);
	free(tmp_old);
	*tmp = (*tmp)->next;
}

/**
 * @brief Get the expanded values of tokens that are linkeds together
 * @param token The token from which we start to get the expanded values
 * @param str_expanded The string that will contain the expanded values
 * (send as char** to be able to modify it in the function)
 * @param shell The shell structure (to get the environment variables)
 * @return The token after the last token that was expanded
*/
t_token	*get_expanded_values(
	t_token *token,
	char **str_gathered,
	t_shell *shell)
{
	t_token	*tmp;
	char	*expanded;

	tmp = token;
	*str_gathered = ft_strdup(tmp->value);
	if (tmp->type == dollar || tmp->type == dquote)
		*str_gathered = arg_expand(shell, tmp->value, tmp->type);
	else
		*str_gathered = ft_strdup(tmp->value);
	while (tmp)
	{
		if (tmp->link_with_next == true && (tmp->next->type == word
				|| tmp->next->type == dollar || tmp->next->type == dquote
				|| tmp->next->type == quote))
		{
			get_exp_val_inside_loop(shell, &tmp, &expanded, str_gathered);
		}
		else
			break ;
	}
	return (tmp);
}
