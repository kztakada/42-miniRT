/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:58:42 by katakada          #+#    #+#             */
/*   Updated: 2025/07/26 21:55:57 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// error messages *************************************************/
# define ERR_PREFIX "Error\n"
# define ERR_INVALID_ARG "Invalid argument (Usage: ./miniRT <scene_file.rt>)\n"

// create_scene
# define ERR_MALLOC_FAIL "Failed to allocate memory\n"

// render_scene_to_mlx
# define ERR_MLX_INIT "Failed to initialize minilibX\n"
# define ERR_CREATE_TH "Failed to create thread\n"
# define ERR_JOIN_TH "Failed to join thread\n"

// obj_funcs
# define ERR_INVALID_CN_ARGS "Invalid arguments for normal calculation\n"
# define ERR_INVALID_COH_ARGS "Invalid arguments for hit calculation\n"
# define ERR_INVALID_GC_ARGS "Invalid arguments for color calculation\n"

// util_foundation
# define ERR_INVALID_C_RATIO "Invalid color ratio (RANGE 0.0 - 1.0)\n"

#endif