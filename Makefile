# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcutte <rcutte@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 12:05:16 by rcutte            #+#    #+#              #
#    Updated: 2024/02/20 14:33:42 by rcutte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


###################### Program ######################

NAME = program

all: $(NAME)

####################### FLAGS #######################

CC = cc
CFLAGS = -Wextra -Wall -Werror -g
READLINE = -lreadline
TERMCAP = -ltermcap

ADD_FLAGS = $(READLINE) $(TERMCAP)

###################### Libft ########################

LIB_PATH = ./libft
LIB_Includes = ./libft/Includes
LIBFT = $(LIB_PATH)/libft.a

$(LIBFT):
	make -sC $(LIB_PATH)
	@if [ -f $(LIB_PATH)/libft.a ]; then \
		echo "$(ARCHIVED)\
╭──────────────────────────────────────────────────╮\n\
│                    Libft Created                 │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	
lib_clean:
	@if [ -f $(LIB_PATH)/Libft/ft_tolower.o ]; then \
		make -sC $(LIB_PATH) clean; \
		echo "$(ORANGE)Libft Objects Cleaned$(RESET)"; \
	fi

lib_fclean:
	@if [ -f $(LIB_PATH)/libft.a ]; then \
		make -sC $(LIB_PATH) fclean; \
		echo "$(ORANGE)Libft Library Delete$(RESET)"; \
	fi

###################### Mandatory ########################

# header path
INCLUDES = ./Includes
# source path
SRC_PATH = ./Sources/mandatory

# files
SRC = main.c \
		$(UTILS) \
		$(LEXER) \
		$(PARSER) \
		$(EXECUTION) \

# objet libft
OBJ = $(addprefix $(SRC_PATH)/,$(SRC:.c=.o))

UTILS = utils/array_of_strings.c \
	utils/free_all.c \

LEXER = lexer/lexer.c \
	lexer/lexer_nodes.c \
	lexer/lexer_read.c \
	lexer/lexer_handler_redir.c \
	lexer/lexer_handler_text.c \
	lexer/lexer_order.c \
	lexer/lexer_check.c \
	lexer/lexer_debug.c \
	lexer/lexer_error.c \

PARSER = parser/parser.c \
	parser/parser_nodes.c \
	parser/parser_nodes_infiles.c \
	parser/parser_nodes_outfiles.c \
	parser/parser_args.c \
	parser/parser_debug.c \
	parser/parser_heredoc_tempo.c \

EXECUTION = execution/builtin.c \
		execution/create_env_list.c \
		execution/exit.c \
		execution/free.c \
		execution/single_process.c \
		execution/utils_exec_struct.c \
		execution/wilcards_bonus.c \
		execution/export.c \
		execution/redirections.c \
		execution/utils_builtin.c \
		execution/utils_pipe.c \
		execution/pipex.c \
		execution/utils_pipex.c \
		execution/utils_heredoc.c \
		execution/heredoc.c \
		execution/execution.c \

###################### Bonus ########################

NAME_BONUS = program_bonus
SRC_BONUS_PATH = ./Sources/bonus
SRC_BONUS = main_bonus.c \

OBJ_BONUS = $(addprefix $(SRC_BONUS_PATH)/,$(SRC_BONUS:.c=.o))

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(ADD_FLAGS) -o $(NAME_BONUS)
	@if [ -f $(NAME_BONUS) ]; then \
		echo "$(COMPILED)\
╭──────────────────────────────────────────────────╮\n\
│             🌟 Program Bonus Compiled 🌟         │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	@if [ ! -f $(NAME_BONUS) ]; then \
		@echo "$(FAILED)\
╭──────────────────────────────────────────────────╮\n\
│         Program Bonus Compilation Failed         │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi

bonus: $(NAME_BONUS)

rebonus: re_msg fclean bonus

##################### Commands ######################

$(NAME): $(LIBFT) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(ADD_FLAGS) -o $(NAME)
	@if [ -f $(NAME) ]; then \
		echo "$(COMPILED)\
╭──────────────────────────────────────────────────╮\n\
│                  Program Compiled                │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi
	@if [ ! -f $(NAME) ]; then \
		echo "$(RED)$(RESET)"; \
		@echo "$(FAILED)\
╭──────────────────────────────────────────────────╮\n\
│            Program Compilation Failed            │\n\
╰──────────────────────────────────────────────────╯\
		$(RESET)";\
	fi

%.o : %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDES) -I$(LIB_Includes) -o $@ $<

clean: clean_msg lib_clean
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean lib_fclean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	
re: re_msg fclean all

####################### Tests ########################

ARGS = 

exec: clean all exec_msg
	@./$(NAME) $(ARGS)

ARGS_BONUS = 

exec_bonus: clean bonus exec_msg
	@./$(NAME_BONUS) $(ARGS_BONUS)

###################### Valgrind/Debug ######################

valgrind: clean all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	--track-origins=yes --trace-children=yes --track-fds=yes --track-origins=yes \
	./$(NAME) $(ARGS)

valgrind_definitely: clean all
	@valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes -s \
	--track-origins=yes --trace-children=yes --track-fds=yes --track-origins=yes \
	./$(NAME) $(ARGS)

valgrind_bonus: clean bonus
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	--track-origins=yes --trace-children=yes --track-fds=yes --track-origins=yes \
	./$(NAME_BONUS) $(ARGS_BONUS)

lldb: clean all
	@lldb ./$(NAME) $(ARGS)

lldb_bonus: clean bonus
	@lldb ./$(NAME_BONUS) $(ARGS_BONUS)

################### Special Target ###################

.PHONY: all clean fclean re \
	bonus rebonus exec exec_bonus valgrind \
	lib_clean lib_fclean lldb lldb_bonus

.SILENT: $(NAME) $(OBJ) $(OBJ_BONUS) $(LIBFT) bonus

###################### Messages ######################
compile_msg:
	@echo "$(COMPILED)\
	╭──────────────────────────────────────────────────╮\n\
	│                  Program Compiled                │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

clean_msg:
	@echo "$(GREY)\
	╭──────────────────────────────────────────────────╮\n\
	│                  Cleaning Objects                │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

re_msg:
	@echo "$(PROGRAM)\
	╭──────────────────────────────────────────────────╮\n\
	│     🚧 Recreation of Program and Libraries 🚧    │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

exec_msg:
	@echo "$(EXEC)\
	╭──────────────────────────────────────────────────╮\n\
	│                 Executing Program                │\n\
	╰──────────────────────────────────────────────────╯\
	$(RESET)"

###################### Colors #######################

# ANSI escape codes for colors and formatting
# Format: \033[<attribute>;<foreground>;<background>m

EXEC = \033[1;94m
PROGRAM = \033[1;95m
COMPILED = \033[1;92m
ARCHIVED = \033[1;93m
FAILED = \033[0;31m

# Attributes (0 to 7)
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m
UNDERLINE = \033[4m
REVERSED = \033[7m

# Foreground Colors (30 to 37)
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

GREY = \033[38;5;240m

# Highlight (Bright) Foreground Colors (90 to 97)
BRIGHT_BLACK = \033[0;90m
BRIGHT_RED = \033[0;91m
BRIGHT_GREEN = \033[0;92m
BRIGHT_YELLOW = \033[0;93m
BRIGHT_BLUE = \033[0;94m
BRIGHT_PURPLE = \033[0;95m
BRIGHT_CYAN = \033[0;96m
BRIGHT_WHITE = \033[0;97m

# Background Colors (40 to 47)
BG_BLACK = \033[0;40m
BG_RED = \033[0;41m
BG_GREEN = \033[0;42m
BG_YELLOW = \033[0;43m
BG_BLUE = \033[0;44m
BG_PURPLE = \033[0;45m
BG_CYAN = \033[0;46m
BG_WHITE = \033[0;47m

# Highlight (Bright) Background Colors (100 to 107)
BG_BRIGHT_BLACK = \033[0;100m
BG_BRIGHT_RED = \033[0;101m
BG_BRIGHT_GREEN = \033[0;102m
BG_BRIGHT_YELLOW = \033[0;103m
BG_BRIGHT_BLUE = \033[0;104m
BG_BRIGHT_PURPLE = \033[0;105m
BG_BRIGHT_CYAN = \033[0;106m
BG_BRIGHT_WHITE = \033[0;107m
