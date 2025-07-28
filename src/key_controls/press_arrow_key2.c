/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:50:04 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 18:55:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_horizontally(t_vector *dir, float angle)
{
	t_vector	rotated_dir;
	float		cos_angle;
	float		sin_angle;

	if (!dir)
		return ((t_vector){0.0F, 0.0F, 0.0F});
	cos_angle = cosf(angle * (float)M_PI / 180.0F);
	sin_angle = sinf(angle * (float)M_PI / 180.0F);
	rotated_dir.x = dir->x * cos_angle - dir->z * sin_angle;
	rotated_dir.y = dir->y;
	rotated_dir.z = dir->x * sin_angle + dir->z * cos_angle;
	return (normalize_vector(rotated_dir));
}

void	rotate_left(t_vector *dir, t_scene *scene __attribute__((unused)))
{
	t_vector	rotated_dir;

	if (!dir)
		return ;
	rotated_dir = rotate_horizontally(dir, ROTATE_ANGLE);
	*dir = rotated_dir;
}

void	rotate_right(t_vector *dir, t_scene *scene __attribute__((unused)))
{
	t_vector	rotated_dir;

	if (!dir)
		return ;
	rotated_dir = rotate_horizontally(dir, -ROTATE_ANGLE);
	*dir = rotated_dir;
}
