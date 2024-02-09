/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:27 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/09 17:56:42 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define PIPE "|"
# define GREATER ">"
# define DGREATER ">>"
# define LESS "<"
# define DLESS "<<"
# define DOLLAR "$"
# define QUOTE "\'"
# define DQUOTE "\""

/**
 * @brief Token types
 * @param pipe_token: Pipe
 * @note pipe_token is called like this because pipe is already used
 * by a function
 * @param greater: Greater than (>)
 * @param dgreater: Greater than (>>)(append)
 * @param less: Less than (<)
 * @param dless: Less than (<<)(heredoc)
 * @param dollar: Dollar ($)
 * @param quote: Quote (')
 * @param dquote: Double quote (")
 * @param word: Word (argument, cmd)
*/
typedef enum
{
	pipe_token,
	greater,
	dgreater,
	less,
	dless,
	dollar,
	quote,
	dquote,
	word
} e_token;

/**
 * @brief Token structure
 * @param value: Token value
 * @param type: Token type
 * @param next: Next token
*/
typedef struct s_token
{
	char			*value;
	e_token			type;
	struct s_token	*next;
}	t_token;

// Lexer

t_token	*lexer(char *input);
void	lexer_rinput(t_token *head, char *input);

// Lexer nodes

t_token	*new_token(char *value, e_token type);
void	add_last_token(t_token *head, char *value, e_token type);

// Lexer management

void	free_tokens(t_token *tokens);
void	lexer_error(t_token *head, char *message);

// Lexer utils

bool	is_whitespace(char c);

// Lexer debug

void	print_tokens(t_token *tokens);

#endif