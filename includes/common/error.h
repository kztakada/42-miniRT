/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:42 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 22:44:55 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// error messages *************************************************/
# define ERR_PREFIX "Error\n"
# define ERR_FORMAT "Format error: "
# define ERR_INVALID_ARG "Invalid argument (Usage: ./miniRT <scene_file.rt>)\n"

// create_scene
# define ERR_MALLOC_FAIL "Failed to allocate memory\n"

// render_scene_to_mlx
# define ERR_MLX_INIT "Failed to initialize minilibX\n"
# define ERR_CREATE_TH "Failed to create thread\n"
# define ERR_JOIN_TH "Failed to join thread\n"
# define ERR_INVALID_SCREEN_SIZE "Invalid screen size 0\n"

// obj_funcs
# define ERR_INVALID_CN_ARGS "Invalid arguments for normal calculation\n"
# define ERR_INVALID_COH_ARGS "Invalid arguments for hit calculation\n"
# define ERR_INVALID_GC_ARGS "Invalid arguments for color calculation\n"

// util_foundation
# define ERR_INVALID_C_RATIO "Invalid color ratio (RANGE 0.0 - 1.0)\n"

// parse
# define ERR_TYPE_IDENT "There are too many type identifiers\n"
# define ERR_L_TYPE_MIXED "l type and L type are mixed up\n"
# define ERR_NUM_ARG "The number of arguments is incorrect\n"
# define ERR_NORMAL_ARG "The normal vector of arguments is incorrect\n"
# define ERR_POS_ARG "The position vector of arguments is incorrect\n"
# define ERR_FOV_ARG "The FOV argument is incorrect\n"
# define ERR_COLOR_ARG "The color of arguments is incorrect\n"
# define ERR_SPECULAR_ARG "The specular of arguments is incorrect\n"
# define ERR_REFRACT_ARG "The refract argument is incorrect\n"
# define ERR_CHECKER_ARG "The checkerboard argument is incorrect\n"
# define ERR_DIAMETER_ARG "The diameter argument is incorrect\n"
# define ERR_HEIGHT_ARG "The height argument is incorrect\n"
# define ERR_ANGLE_ARG "The angle argument is incorrect\n"
# define ERR_BRIGHT_ARG "The brightness ratio argument is incorrect\n"
# define ERR_INVALID_VALUE "An invalid value has been entered\n"
# define ERR_NOT_NUMBER "The value entered is not a number\n"
# define ERR_BOOL "The value entered is not 1 or 0\n"
# define ERR_NO_FILE "The texture or bumpmap file does not exist\n"
# define ERR_NO_RT "The .rt file is not found\n"
# define ERR_NO_IDENT "Incorrect identifier\n"

#endif