# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2021/02/18 22:37:24 by fyusuf-a         ###   ########.fr        #
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

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror 
#CFLAGS = -Wall -Wextra

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address 
endif

# ------------------------------------------------------------------------------

INC_DIR = includes

HEADERS += $(INC_DIR)/libft.h 
HEADERS += $(INC_DIR)/get_next_line.h 

#ifeq ($(TEST), 1)
	#HEADERS += $(INC_DIR)/ft_sprintf.h
#else
	HEADERS += $(INC_DIR)/ft_printf.h
#endif

OBJ = $(SRC:.c=.o)

SRC = ft_atoi.c \
	ft_atoi_strict.c \
	ft_atoi_mv.c \
	ft_atof.c \
	ft_atof_mv.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isblank.c \
	ft_isnumber.c \
	ft_min.c \
	ft_max.c \
	ft_itoa.c \
	ft_itoa_base.c \
	ft_ptoa.c \
	ft_utoa.c \
	ft_utoa_base.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_memdel.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c	\
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_split_blank.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_strdelchar.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_lstdel_first.c \
	ft_lstadd_back.c \
	ft_lstadd_back_elem.c \
	ft_lstadd_front_elem.c \
	ft_lstremove_if.c \
	ft_lstfind_content.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lsttotab.c \
	ft_lsttotabold.c \
	ft_dlstnew.c \
	ft_dlstsize.c \
	ft_dlstadd_back.c \
	ft_dlstclear.c \
	ft_dlstiter.c \
	ft_dlstlast.c \
	ft_dlstfirst.c \
	ft_tabtodlst.c \
	ft_abs.c \
	ft_pass_spaces.c \
	ft_realloc.c \
	ft_split_dict.c
	#ft_sprintf.c \

SRC	+= ft_printf_main.c ft_printf_main2.c ft_printf_parse_format.c ft_printf_parse_format2.c ft_printf_print.c ft_printf_print_str.c ft_printf_print_int.c ft_printf_print_int2.c ft_printf_utilities.c
SRC	+= ft_printf_utilities2.c ft_printf_format.c ft_printf_print_nothing.c ft_printf_print_double.c ft_printf_print_double2.c ft_printf_print_scientific.c ft_printf_print_g.c

#ifeq ($(TEST), 1)
	#shell echo "compiling test mode buffer.c"
	#SRC += sbuffer.c 
	#SRC += ft_sprintf.c 
#else
#endif
	
PRINTF_DIR = ft_printf

# ------------------------------------------------------------------------------

vpath %.c src
vpath %.c src/$(PRINTF_DIR) 

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

$(NAME): $(OBJ) 
	ar rc $(NAME) $^
	ranlib $(NAME)

%.o : %.c $(HEADERS)
	$(CC) -I $(INC_DIR) -c $(CFLAGS) $< 

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
