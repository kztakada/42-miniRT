/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:07:20 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 19:36:28 by katakada         ###   ########.fr       */
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
# define MAX_RAND_SAMPLING 1

// rendering
# define AIR_REFRACT_INDEX 1.0F
# define MIN_OBJ_REFRACT_INDEX 1.0F

// material
# define CHECKERBOARD_SIZE 10.0F

// raytracing
# define MAX_RECURSION_DEPTH 5

// key controls
# define MOVE_SPEED 1.0F
# define ROTATE_ANGLE 10.0F
# define UV_ROTATE_ANGLE 0.05F
# define BRIGHTNESS_STEP 0.1F

#endif