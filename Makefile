# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakada <katakada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 21:01:15 by katakada          #+#    #+#              #
#    Updated: 2025/08/11 12:42:44 by katakada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	miniRT

CC				=	cc -O2 #-fopt-info-inline
BONUS_CC		=	cc -DSTB_IMAGE_IMPLEMENTATION
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address,undefined
CFLAGS			=	-Wall -Wextra -Werror

INC_MAIN		=	-I includes/mandatory/
INCS			=	-I includes/common/ $(INC_MAIN) -I $(LIBFT_DIR) -I $(MLX_DIR)

SRC_PATH		=	src/

SRC_MAIN		=	$(SRC_PATH)use_only_mandatory/calc_screen_dot_pos.c \
					$(SRC_PATH)use_only_mandatory/main.c \
					$(SRC_PATH)use_only_mandatory/run_renderer.c \
					$(SRC_PATH)use_only_mandatory/set_material.c \

SRCS			=	$(SRC_MAIN) \
					$(SRC_PATH)create_scene/create_scene.c \
					$(SRC_PATH)create_scene/format_check_env.c \
					$(SRC_PATH)create_scene/format_check_objs.c \
					$(SRC_PATH)create_scene/format_check_util2.c \
					$(SRC_PATH)create_scene/format_check_util.c \
					$(SRC_PATH)create_scene/parse_obj.c \
					$(SRC_PATH)create_scene/parse_obj_cone.c \
					$(SRC_PATH)create_scene/parse_obj_cylinder.c \
					$(SRC_PATH)create_scene/parse_obj_plane.c \
					$(SRC_PATH)create_scene/parse_obj_sphere.c \
					$(SRC_PATH)create_scene/parse_one_line_on_scene.c \
					$(SRC_PATH)create_scene/parse_scene_env.c \
					$(SRC_PATH)create_scene/set_info.c \
					$(SRC_PATH)key_controls/press_arrow_key2.c \
					$(SRC_PATH)key_controls/press_arrow_key3.c \
					$(SRC_PATH)key_controls/press_arrow_key4.c \
					$(SRC_PATH)key_controls/press_arrow_key.c \
					$(SRC_PATH)key_controls/press_move_key2.c \
					$(SRC_PATH)key_controls/press_move_key.c \
					$(SRC_PATH)key_controls/press_utils_key.c \
					$(SRC_PATH)key_controls/print_scene_rt_format.c \
					$(SRC_PATH)key_controls/reset_scene.c \
					$(SRC_PATH)key_controls/select_light.c \
					$(SRC_PATH)key_controls/set_key_controls.c \
					$(SRC_PATH)render_scene_to_mlx/calc_closest_obj.c \
					$(SRC_PATH)render_scene_to_mlx/calc_lights_effect.c \
					$(SRC_PATH)render_scene_to_mlx/print_rendering_console.c \
					$(SRC_PATH)render_scene_to_mlx/raytracing.c \
					$(SRC_PATH)render_scene_to_mlx/render_mlx_image.c \
					$(SRC_PATH)render_scene_to_mlx/render_scene_to_mlx.c \
					$(SRC_PATH)setup_scene/setup_camera_screen.c \
					$(SRC_PATH)setup_scene/setup_scene.c \
					$(SRC_PATH)util_foundation/calc_color2.c \
					$(SRC_PATH)util_foundation/calc_color3.c \
					$(SRC_PATH)util_foundation/calc_color.c \
					$(SRC_PATH)util_foundation/calc_vector2.c \
					$(SRC_PATH)util_foundation/calc_vector3.c \
					$(SRC_PATH)util_foundation/calc_vector.c \
					$(SRC_PATH)util_foundation/expand_math.c \
					$(SRC_PATH)util_foundation/get_ref_vector.c \
					$(SRC_PATH)obj_funcs/calc_bump_effects.c \
					$(SRC_PATH)obj_funcs/calc_normal2.c \
					$(SRC_PATH)obj_funcs/calc_normal_bump.c \
					$(SRC_PATH)obj_funcs/calc_normal.c \
					$(SRC_PATH)obj_funcs/calc_obj_hit2.c \
					$(SRC_PATH)obj_funcs/calc_obj_hit3.c \
					$(SRC_PATH)obj_funcs/calc_obj_hit.c \
					$(SRC_PATH)obj_funcs/calc_obj_hit_util.c \
					$(SRC_PATH)obj_funcs/calc_uv_map2.c \
					$(SRC_PATH)obj_funcs/calc_uv_map.c \
					$(SRC_PATH)obj_funcs/change_size.c \
					$(SRC_PATH)obj_funcs/get_color2.c \
					$(SRC_PATH)obj_funcs/get_color3.c \
					$(SRC_PATH)obj_funcs/get_color.c \
					$(SRC_PATH)obj_funcs/get_dir.c \
					$(SRC_PATH)obj_funcs/get_pos.c \
					$(SRC_PATH)obj_funcs/print_focused_obj.c \
					$(SRC_PATH)obj_funcs/print_rt.c \
					$(SRC_PATH)obj_funcs/reset_obj.c \
					$(SRC_PATH)obj_funcs/set_local_xyz.c \
					$(SRC_PATH)utils/free_scene.c \
					$(SRC_PATH)utils/handle_shorter.c \
					$(SRC_PATH)utils/put_error.c \

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
ARGS ?= scene/mandatory.rt

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
    SRC_MAIN =	$(SRC_PATH)use_only_bonus/calc_screen_dot_pos_bonus.c \
				$(SRC_PATH)use_only_bonus/main_bonus.c \
				$(SRC_PATH)use_only_bonus/run_renderer_bonus.c \
				$(SRC_PATH)use_only_bonus/set_material_bonus.c \

	CC = $(BONUS_CC)
endif

all:	$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) $(MLX) $(FRAMEWORKS) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.c
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
