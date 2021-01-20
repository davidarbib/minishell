# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 12:23:24 by darbib            #+#    #+#              #
#    Updated: 2021/01/20 15:09:15 by fyusuf-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE = 		'\033[0;34m'
GREEN = 	'\033[0;32m'
LIGHTBLUE = '\033[1;34m'
RED = 		'\033[0;31m'
YELLOW = 	'\033[1;33m'
ORANGE = 	'\033[0;33m'
MAGENTA = 	'\033[0;35m'
RESET = 	'\033[0m'

NAME = minishell
CFLAGS= -Wall -Wextra -Werror -fsanitize=address
CC = clang

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address
endif

# ------------------------------------------------------------------------------

OBJ_DIR = ./objs/
SRC_DIR = ./srcs/

# ------------------------------------------------------------------------------

LIBFT_DIR = ./libft/
LIBFT = libft.a
LIB_LIBFT += $(addprefix $(LIBFT_DIR), $(LIBFT))

LDFLAGS = $(addprefix -L, $(LIBFT_DIR))
LDFLAGS += -lft
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

INC_DIRS = ./libft/includes \
		  ./includes

INC = $(addprefix -I, $(INC_DIRS))

SRC = lexer.c \
	  parser.c \
	  token.c \
	  error.c \
	  destroy.c \
	  char_handling_fts.c \
	  lexer_fsm_tools.c \
	  assignment_detector.c \
	  assignment_parser.c \
	  ionumber_detector.c \
	  redirection_parser.c \
	  isredirection_op.c \
		test.c

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJ) $(LIB_LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)
	@echo $(GREEN) $@ " is ready to use !" $(RESET)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p objs
	@echo $(BLUE) "compiling" $< $(RESET)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(LIB_LIBFT) :
	@echo "Compile libft.."
	@make -C $(LIBFT_DIR)

clean :
	@echo $(MAGENTA) "Cleaning objs..." $(RESET)
	@rm -rf $(OBJ_DIR)
	@rm -f $(LIBS)
	@make clean -C $(LIBFT_DIR)
	@echo $(MAGENTA) "...done" $(RESET)

fclean : clean
	@echo $(MAGENTA) "Total cleaning..." $(RESET)
	@rm -f $(NAME)
	@rm -f $(LIB_LIBFT)
	@echo $(MAGENTA) "...done" $(RESET)

test: 

re : fclean all
