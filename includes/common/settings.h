/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:07:20 by katakada          #+#    #+#             */
/*   Updated: 2025/07/23 01:25:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

// window title
# define WIN_TITLE "MiniRT"

// window size
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// camera settings
# define FOCAL_FACTOR 1.0F // 焦点距離係数

// multi-threading
# define MAX_THREADS 8

// sampling
# define MAX_FIX_SAMPLING 4
/* MAX_FIX_SAMPLING requires perfect square */
# define MAX_RAND_SAMPLING 100

// material
# define CHECKERBOARD_SIZE 1.0

// raytracing
# define MAX_RECURSION_DEPTH 5

#endif