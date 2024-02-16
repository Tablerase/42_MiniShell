/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:51 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/16 13:57:47 by rcutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// STD
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
// ERRNO
# include <errno.h>
// READLINE
# include <readline/readline.h>
# include <readline/history.h>
// SYSTEM
# include <sys/wait.h>
// SIGNAL
# include <signal.h>
// STAT
# include <sys/stat.h>
# include <time.h>
// TERM
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

// Prompt of Minishell
# define PROMPT "\e[1;38;5;141mMiniShell\e[1;33m ➜ \033[0m"

typedef struct s_outf
{
	char			*file;
	bool			append;
	struct s_outf	*next;
}	t_outf;

typedef struct s_inf
{
	char			*file;
	bool			heredoc;
	struct s_inf	*next;
}	t_inf;

/**
 * * Structure for the heredocs
 * @param heredoc_path The path of the heredoc
 * @param next The next heredoc
*/
typedef struct s_heredocs
{
	char				*heredoc_path;
	struct s_heredocs	*next;
}	t_heredocs;

/**
 * * Structure for the command table
 * @param cmd The command
 * @param args The arguments
 * @param infile The input files array (null terminated)
 * @param outfile The output files (and append) array (null terminated)
 * @param next The next command
*/
typedef struct s_table
{
	char			*cmd;
	char			**args;
	t_inf			*infd_head;
	t_outf			*outfd_head;
	struct s_table	*next;
}	t_table;

/**
 * * Structure for the shell
 * @param env The environment variables of minishell
 * @param stdin The standard input of minishell
 * @param stdout The standard output of minishell
 * @param table_head The commands table
 * @param heredocs The heredocs
*/
typedef struct s_shell
{
	char		**env;
	int			stdin;
	int			stdout;
	t_table		*table_head;
	t_heredocs	*heredocs;
}	t_shell;

// LIB needing upper structs to be defined

// LIBFT
# include "../libft/Includes/libft.h"
// Color
# include "color.h"
// Utils
# include "utils.h"
// Lexer
# include "lexer.h"
// Parser
# include "parser.h"

#endif