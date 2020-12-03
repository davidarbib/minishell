# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2020/08/24 21:09:04 by darbib           ###   ########.fr        #
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

NAME = miniRT
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
UNAME_S = $(shell uname -s)

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address
endif

# ------------------------------------------------------------------------------

LIB_DIR = /usr/lib/
OBJ_DIR = ./objs/
SRC_DIR = ./srcs/

# ------------------------------------------------------------------------------

LIBFT_DIR = ./libft/
LIBFT = libft.a
LIB_LIBFT += $(addprefix $(LIBFT_DIR), $(LIBFT))

LDFLAGS = $(addprefix -L, $(LIBFT_DIR))

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

ifeq ($(UNAME_S),Linux)
	MLX_DIR = ./minilibx_linux/
	MLX = libmlx.a
	LIB_MLX = $(addprefix $(MLX_DIR), $(MLX))
	LDFLAGS += $(addprefix -L, $(MLX_DIR))
	LDFLAGS += -lm -lmlx -lX11 -lXext -lft
else
	MLX_DIR = ./minilibx_macos/
	MLX = libmlx.dylib
	LIB_MLX = $(addprefix $(MLX_DIR), $(MLX))
	LDFLAGS += -lft -dylib $(LIB_MLX)
endif

INC_DIRS = ./libft/includes \
		  ./includes \
		  $(MLX_DIR)

INC = $(addprefix -I, $(INC_DIRS))

LIBS = $(LIB_MLX) $(LIB_LIBFT)

SRC = camera.c \
	cylinder.c \
	destroy.c \
	error.c \
	exit.c \
	init.c \
	graphic.c \
	image.c \
	omnilight.c \
	parse_utils.c \
	parse_utils2.c \
	parse_utils3.c \
	vector.c \
	vect_product.c \
	vect_projection.c \
	parsing.c \
	handle_line.c \
	scene_rotation.c \
	scene_rotation2.c \
	scene_rotation3.c \
	scene_rotation4.c \
	plane.c \
	rt_buffer.c \
	sphere.c \
	square.c \
	square2.c \
	minitools.c \
	turn.c \
	turn2.c \
	move.c \
	move2.c \
	raytrace.c \
	light_casting.c \
	raytrace2.c \
	raytrace_savebmp.c \
	rayplane.c \
	rayvolume.c \
	keyboard_actions.c \
	scene_setup.c \
	scene_move.c \
	scene_move2.c \
	set_objs.c \
	set_obj2.c \
	update.c \
	bitmap.c \
	matrix.c \
	matrix_gen.c \
	matrix_inversion.c \
	loop_intersect.c \
	observer.c \
	illumination.c \
	get_hit_data.c \
	endian.c \
	triangle.c

ifeq ($(DRAFT), 1)
	SRC += draft.c
else
	SRC += minirt.c
endif

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

bonus : $(NAME)

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)
	@echo $(GREEN) $@ builded ! $(RESET)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p objs
	@echo $(BLUE) "compiling" $< $(RESET)
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(MLX_DIR)$(MLX) :
	@echo "Compile mlx..."
	@make -C $(MLX_DIR)

$(LIBFT_DIR)$(LIBFT) :
	@echo "Compile libft.."
	@make -C $(LIBFT_DIR)

clean :
	@echo $(MAGENTA) "Cleaning objs..." $(RESET)
	@rm -rf $(OBJ_DIR)
	@rm -f $(LIBS)
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo $(MAGENTA) "...done" $(RESET)

fclean : clean
	@echo $(MAGENTA) "Total cleaning..." $(RESET)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo $(MAGENTA) "...done" $(RESET)

re : fclean all
