/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:16 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:41:11 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_camera_vertically(t_vector *current_dir, float angle)
{
	t_vector	rotated_dir;
	float		vertical_limit;
	float		y_dot;
	float		y_delta;

	if (!current_dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	y_dot = fabsf(vectors_dot(*current_dir, up_dir()));
	y_delta = sinf(angle * (float)M_PI / 180.0F);
	vertical_limit = 1.0f - fabsf(y_delta);
	if (y_dot > vertical_limit)
	{
		if (current_dir->y < 0 && angle > 0)
			return ((t_vector){current_dir->x, -1.0F + 1e-6f, current_dir->z});
		if (current_dir->y > 0 && angle < 0)
			return ((t_vector){current_dir->x, 1.F - 1e-6f, current_dir->z});
	}
	rotated_dir = (t_vector){current_dir->x, current_dir->y - y_delta,
		current_dir->z};
	return (rotated_dir);
}

static t_vector	rotate_obj_vertically(t_vector *dir, float angle,
		t_scene *scene)
{
	t_vector	rotated_dir;

	if (!dir || !scene)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	rotated_dir = calc_rodrigues_rotation(*dir, right_dir(), angle);
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
