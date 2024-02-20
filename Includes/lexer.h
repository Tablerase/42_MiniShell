/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:27 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 11:16:44 by abourgeo         ###   ########.fr       */
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
 * @brief Handler types
 * @param found: Token found
 * @param not_found: Token not found
 * @param error: Error
 * @note This is used to handle the return of the lexer functions
 * to know if the token was found or not and if there was an error
*/
typedef enum
{
	found,
	not_found,
	error
}	e_handler;

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

/**
 * @brief Lexer structure
 * @param head: Head of the tokens
*/
typedef struct s_lexer
{
	t_token	*head;
}	t_lexer;

// Lexer

bool		lexer(char *input, t_lexer *syntax);
bool		lexer_rinput(t_lexer *syntax, char *input);
bool		lexer_check_order(t_token *head);

// Lexer handlers

e_handler	lexer_handle_space(char *input, int *i);
e_handler	lexer_handle_pipe(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_greater(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_less(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_dollar(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_quote(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_dquote(t_lexer *syntax, char *input, int *i);
e_handler	lexer_handle_word(t_lexer *syntax, char *input, int *i);

// Lexer nodes

t_token		*new_token(char *value, e_token type);
void		add_last_token(t_lexer *syntax, char *value, e_token type);

// Lexer management

void		free_tokens(t_token *tokens);
void		lexer_error(t_token *head, char *message);

// Lexer utils

bool		is_whitespace(char c);
bool		is_quotes(char c);
bool		is_end_of_str(char *str);
bool		is_metachar(char c);

// Lexer debug

void		print_tokens(t_token *tokens);

#endif