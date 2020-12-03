# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2020/07/17 19:37:36 by darbib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
#CFLAGS = -Wall -Wextra -Werror 
CFLAGS = -Wall -Wextra

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITY), 1)
	CFLAGS += -fsanitize=address 
endif

# ------------------------------------------------------------------------------

INC_DIR = includes

HEADERS += $(INC_DIR)/libft.h 
HEADERS += $(INC_DIR)/get_next_line.h 

ifeq ($(TEST), 1)
	HEADERS += $(INC_DIR)/ft_sprintf.h
else
	HEADERS += $(INC_DIR)/ft_printf.h
endif

OBJ = $(SRC:.c=.o)

SRC = ft_atoi.c \
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
	ft_putchar_fd.c \
	ft_putendl_fd.c	\
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_split_blank.c \
	ft_strchr.c \
	ft_strdup.c \
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
	ft_lstadd_back.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lsttotab.c \
	ft_abs.c \
	ft_pass_spaces.c \
	ft_printf.c \
	ft_sprintf.c \
	conversion.c \
	utils.c \
	nocs_convert.c \
	di_convert.c \
	u_convert.c \
	x_convert.c \
	p_convert.c

ifeq ($(TEST), 1)
	#shell echo "compiling test mode buffer.c"
	SRC += sbuffer.c 
	SRC += ft_sprintf.c 
else
	SRC += buffer.c
	SRC += ft_printf.c 
endif
	
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
