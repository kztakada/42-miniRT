# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakada <katakada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 20:13:13 by katakada          #+#    #+#              #
#    Updated: 2025/07/30 16:06:57 by katakada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	miniRT

CC				=	cc -O2 #-fopt-info-inline
BONUS_CC		=	cc -DSTB_IMAGE_IMPLEMENTATION
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address,undefined
CFLAGS			=	-Wall -Wextra -Werror

INC_MAIN		=	-I includes/mandatory/
INCS			=	-I includes/common/ $(INC_MAIN) -I $(LIBFT_DIR) -I $(MLX_DIR)

SRCS_PATH		=	src/
SRCS_MAIN		=	$(wildcard src/use_only_mandatory/*.c)
SRCS			=	$(SRCS_MAIN) \
					$(wildcard src/set_default_scene/*.c) \
					$(wildcard src/parse/*.c) \
					$(wildcard src/create_scene/*.c) \
					$(wildcard src/key_controls/*.c) \
					$(wildcard src/render_scene_to_mlx/*.c) \
					$(wildcard src/setup_scene/*.c) \
					$(wildcard src/util_foundation/*.c) \
					$(wildcard src/obj_funcs/*.c) \
					$(wildcard src/utils/*.c) \

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:src/%.c=objs/%.o)

LIBFT_DIR		=	libraries/
LIBFT			=	$(LIBFT_DIR)libft.a

MLX_DIR			=	minilibx/
MLX				=	$(MLX_DIR)libmlx_Linux.a
FRAMEWORKS		=	-lXext -lX11 -lm -lbsd

MLX_MAC			=	$(MLX_DIR)libmlx_Darwin.a
FRAMEWORKS_MAC	=	-L /usr/X11/include/../lib -lXext -lX11

ISDEBUG = 0
ARGS ?= scene/sample.rt

ifeq ($(ISDEBUG), 1)
	CC = $(DEBUG_CC)
endif

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	INCS += -I /usr/X11/include
    MLX = $(MLX_MAC)
    FRAMEWORKS = $(FRAMEWORKS_MAC)
endif

ifdef WITH_BONUS
    INC_MAIN = -I includes/bonus/
    SRCS_MAIN =	$(wildcard src/use_only_bonus/*.c)
	CFLAGS += -DSTB_IMAGE_IMPLEMENTATION -D IS_DEBUG=1 -g -fsanitize=address,undefined
endif

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) $(MLX) $(FRAMEWORKS) -o $(NAME)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@


bonus:
	@make WITH_BONUS=1

debug:
	make fclean
	$(MAKE) ISDEBUG=1 all

va:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(MLX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)


clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS_PATH)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)
	rm -rf $(OBJS_PATH)
	rm -f $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean debug va re
