/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:51 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/12 18:06:27 by rcutte           ###   ########.fr       */
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

// LIBFT
# include "../libft/Includes/libft.h"
// Color
# include "color.h"
// Lexer
# include "lexer.h"

# define PROMPT "minishell$> "

typedef struct s_outf
{
	char	*file;
	bool	append;
}	t_outf;

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
	char			**infile;
	t_outf			**outfile;
	struct s_table	*next;
}	t_table;

typedef struct s_shell
{
	char		**env;
	int			stdin;
	int			stdout;
	t_table		*table_head;
	t_heredocs	*heredocs;
}	t_shell;

#endif