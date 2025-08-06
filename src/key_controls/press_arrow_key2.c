/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:04 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 01:43:34 by katakada         ###   ########.fr       */
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

static t_vector	rotate_obj_horizontally(t_vector *dir, float angle)
{
	t_vector	rotated_dir;
	float		dot_product;
	t_vector	cross_product;

	t_vector axis_u, axis_v;
	float cos_angle, sin_angle;
	if (!dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	// handle_gimbal_lock_uv_axesと同じ方法で安定した軸を取得
	if (!handle_gimbal_lock_uv_axes(*dir, &axis_u, &axis_v))
	{
		// フォールバック: 元の実装
		cos_angle = cosf(angle * (float)M_PI / 180.0F);
		sin_angle = sinf(angle * (float)M_PI / 180.0F);
		rotated_dir.x = dir->x * cos_angle - dir->z * sin_angle;
		rotated_dir.y = dir->y;
		rotated_dir.z = dir->x * sin_angle + dir->z * cos_angle;
		return (normalize_vector(rotated_dir));
	}
	cos_angle = cosf(angle * (float)M_PI / 180.0F);
	sin_angle = sinf(angle * (float)M_PI / 180.0F);
	// axis_uを回転軸として使用（水平方向）
	// *dir を axis_u 軸周りに回転
	dot_product = vectors_dot(*dir, axis_u);
	cross_product = cross_vector(axis_u, *dir);
	// Rodriguesの回転公式
	rotated_dir.x = dir->x * cos_angle + cross_product.x * sin_angle + axis_u.x
		* dot_product * (1.0f - cos_angle);
	rotated_dir.y = dir->y * cos_angle + cross_product.y * sin_angle + axis_u.y
		* dot_product * (1.0f - cos_angle);
	rotated_dir.z = dir->z * cos_angle + cross_product.z * sin_angle + axis_u.z
		* dot_product * (1.0f - cos_angle);
	return (normalize_vector(rotated_dir));
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
