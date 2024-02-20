/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:51 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/20 11:17:36 by abourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// STD
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
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
# include <bits/sigaction.h>
# include <asm-generic/signal-defs.h>
// STAT
# include <sys/stat.h>
# include <time.h>
// TERM
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

// Prompt of Minishell
# define PROMPT "\e[1;38;5;141mMiniShell\e[1;33m ➜ \033[0m"

extern int	g_signal;

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
 * Structure that stores the list of environment variables.
 * Used by export, env and unset.
 * @param name The name of the variable.
 * @param value The expansion of the associated variable.
 * @param next The next node of the list.
*/
typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

/**
 * * Structure for the shell
 * @param env The environment variables of minishell
 * @param std_in The standard input of minishell
 * @param std_out The standard output of minishell
 * @param table_head The commands table
 * @param heredocs The heredocs
*/
typedef struct s_shell
{
	t_env_list	**env;
	int			std_in;
	int			std_out;
	t_table		*table_head;
	t_heredocs	*heredocs;
	int			exit_code;
}	t_shell;

/**
 * Structure that stores all the program's data.
 * @param env_list The list containing the environment variables.
 * @param export_list The list containing the environment variables (also 
 * the non-initialized variables).
 * @param shell The data returned by the parser.
*/
typedef struct s_exec
{
	t_env_list	**export_list;
	t_shell		*shell;
}	t_exec;

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
// Exec
# include "exec.h"


#endif
