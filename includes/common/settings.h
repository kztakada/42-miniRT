/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:07:20 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 10:48:17 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

// window title
# define WIN_TITLE "MiniRT"

// window size
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// background color
# define BG_COLOR_R 137
# define BG_COLOR_G 189
# define BG_COLOR_B 222

// camera settings
# define FOCAL_FACTOR 1.0F // 焦点距離係数

// multi-threading
# define MAX_THREADS 8

// sampling
# define MAX_FIX_SAMPLING 4
/* MAX_FIX_SAMPLING requires perfect square */
# define MAX_RAND_SAMPLING 2

// rendering
# define AIR_REFRACT_INDEX 1.0F
# define MIN_OBJ_REFRACT_INDEX 1.0F

// material
# define CHECKERBOARD_SIZE 10.0F
# define TEXTURE_TILE_SCALE 0.001F
# define BUMP_HEIGHT_SCALE 100.0F
# define BUMP_MAX_RANGE 0.5F

// raytracing
# define MAX_RECURSION_DEPTH 5

// key controls
# define MOVE_SPEED 1.0F
# define ROTATE_ANGLE 5.0F
# define UV_ROTATE_ANGLE 0.05F
# define BRIGHTNESS_STEP 0.1F

#endif