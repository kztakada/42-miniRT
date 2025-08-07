/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:04 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 13:22:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_camera_horizontally(t_vector *current_dir, float angle)
{
	t_vector	rotated_dir;

	if (!current_dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	rotated_dir = calc_rodrigues_rotation(*current_dir, up_dir(), angle);
	return (rotated_dir);
}

static t_vector	rotate_obj_horizontally(t_vector *current_dir, float angle)
{
	t_vector	rotated_dir;

	if (!current_dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	rotated_dir = calc_rodrigues_rotation(*current_dir, forward_dir(), angle);
	return (rotated_dir);
}

void	rotate_left(t_mode_select mode, t_vector *dir, t_scene *scene)
{
	if (!dir)
		return ;
	if (mode == CAMERA_MODE)
	{
		*dir = rotate_camera_horizontally(dir, ROTATE_ANGLE);
		setup_camera_screen(scene);
	}
	else
		*dir = rotate_obj_horizontally(dir, -ROTATE_ANGLE);
}

void	rotate_right(t_mode_select mode, t_vector *dir, t_scene *scene)
{
	if (!dir)
		return ;
	if (mode == CAMERA_MODE)
	{
		*dir = rotate_camera_horizontally(dir, -ROTATE_ANGLE);
		setup_camera_screen(scene);
	}
	else
		*dir = rotate_obj_horizontally(dir, ROTATE_ANGLE);
}
