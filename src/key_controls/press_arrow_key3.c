/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:16 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 02:00:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_camera_vertically(t_vector *current_dir, float angle)
{
	t_vector	rotated_dir;
	float		vertical_limit;
	float		y_dot;

	if (!current_dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	// Y軸との平行度をチェック
	y_dot = fabsf(vectors_dot(*current_dir, up_dir()));
	vertical_limit = 1.0f - fabsf(sinf(ROTATE_ANGLE * (float)M_PI / 180.0F));
	// ジンバルロック回避
	if (y_dot > vertical_limit)
	{
		if (current_dir->y < 0 && angle > 0)
			return (*current_dir); // 下向きで下回転は無効
		if (current_dir->y > 0 && angle < 0)
			return (*current_dir); // 上向きで上回転は無効
	}
	rotated_dir = calc_rodrigues_rotation(*current_dir, right_dir(), angle);
	return (rotated_dir);
}

static t_vector	rotate_obj_vertically(t_vector *dir, float angle,
		t_scene *scene)
{
	t_vector	rotated_dir;
	t_vector	axis_u;
	t_vector	axis_v;
	t_vector	vertical_axis;
	float		sin_angle;

	if (!dir || !scene)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	// handle_gimbal_lock_uv_axesと同じ方法で安定した軸を取得
	if (!handle_gimbal_lock_uv_axes(*dir, &axis_u, &axis_v))
	{
		// フォールバック: 簡単な垂直回転
		vertical_axis = normalize_vector(scene->screen.y_per_pixel);
		sin_angle = sinf(angle * (float)M_PI / 180.0F);
		rotated_dir = add_vectors(*dir, scale_vector(sin_angle, vertical_axis));
		return (normalize_vector(rotated_dir));
	}
	rotated_dir = calc_rodrigues_rotation(*dir, axis_v, angle);
	return (rotated_dir);
}

void	rotate_up(t_mode_select mode, t_vector *dir, t_scene *scene)
{
	if (!dir || !scene)
		return ;
	if (mode == CAMERA_MODE)
	{
		*dir = rotate_camera_vertically(dir, -ROTATE_ANGLE);
		setup_camera_screen(scene);
	}
	else
		*dir = rotate_obj_vertically(dir, ROTATE_ANGLE, scene);
}

void	rotate_down(t_mode_select mode, t_vector *dir, t_scene *scene)
{
	if (!dir || !scene)
		return ;
	if (mode == CAMERA_MODE)
	{
		*dir = rotate_camera_vertically(dir, ROTATE_ANGLE);
		setup_camera_screen(scene);
	}
	else
		*dir = rotate_obj_vertically(dir, -ROTATE_ANGLE, scene);
}
