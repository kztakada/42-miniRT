/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:16 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 18:55:42 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_vertically(t_vector *dir, float angle, t_scene *scene)
{
	t_vector	rotated_dir;
	t_vector	vertical_axis;
	float		sin_angle;

	if (!dir || !scene)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	sin_angle = sinf(angle * (float)M_PI / 180.0F);
	vertical_axis = normalize_vector(scene->screen.y_per_pixel);
	rotated_dir = add_vectors(*dir, scale_vector(sin_angle, vertical_axis));
	return (normalize_vector(rotated_dir));
}

// static void rotate_vertically(t_vector *dir, float angle)
// {
// 	t_vector	rotated_dir;
// 	float		cos_angle;
// 	float		sin_angle;

// 	if (!dir)
// 		return ((t_vector){0.0F, 0.0F, 0.0F});
// 	cos_angle = cosf(angle * (float)M_PI / 180.0F);
// 	sin_angle = sinf(angle * (float)M_PI / 180.0F);
// 	rotated_dir.x = dir->x * cos_angle - dir->y * sin_angle;
// 	rotated_dir.y = dir->x * sin_angle + dir->y * cos_angle;
// 	rotated_dir.z = dir->z; // z remains unchanged
// 	return (normalize_vector(rotated_dir));
// }

void	rotate_up(t_vector *dir, t_scene *scene)
{
	t_vector	rotated_dir;

	if (!dir || !scene)
		return ;
	rotated_dir = rotate_vertically(dir, ROTATE_ANGLE, scene);
	*dir = rotated_dir;
}

void	rotate_down(t_vector *dir, t_scene *scene)
{
	t_vector	rotated_dir;

	if (!dir || !scene)
		return ;
	rotated_dir = rotate_vertically(dir, -ROTATE_ANGLE, scene);
	*dir = rotated_dir;
}
