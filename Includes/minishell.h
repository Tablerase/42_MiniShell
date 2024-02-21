/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgeo <abourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:11:51 by rcutte            #+#    #+#             */
/*   Updated: 2024/02/21 06:54:46 by abourgeo         ###   ########.fr       */
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

// LIB needing upper structs to be defined

// Exec
# include "exec.h"
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

// Prompt of Minishell
# define PROMPT "\e[1;38;5;141mMiniShell\e[1;33m ➜ \033[0m"


#endif
