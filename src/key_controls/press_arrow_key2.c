/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:04 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 01:59:36 by katakada         ###   ########.fr       */
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
	t_vector	axis_u;
	t_vector	axis_v;
	float		cos_angle;
	float		sin_angle;

	if (!current_dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	// handle_gimbal_lock_uv_axesと同じ方法で安定した軸を取得
	if (!handle_gimbal_lock_uv_axes(*current_dir, &axis_u, &axis_v))
	{
		// フォールバック: 元の実装
		cos_angle = cosf(angle * (float)M_PI / 180.0F);
		sin_angle = sinf(angle * (float)M_PI / 180.0F);
		rotated_dir.x = current_dir->x * cos_angle - current_dir->z * sin_angle;
		rotated_dir.y = current_dir->y;
		rotated_dir.z = current_dir->x * sin_angle + current_dir->z * cos_angle;
		return (normalize_vector(rotated_dir));
	}
	rotated_dir = calc_rodrigues_rotation(*current_dir, axis_u, angle);
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
		*dir = rotate_obj_horizontally(dir, ROTATE_ANGLE);
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
		*dir = rotate_obj_horizontally(dir, -ROTATE_ANGLE);
}
