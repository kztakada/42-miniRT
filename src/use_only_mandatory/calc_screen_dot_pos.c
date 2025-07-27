/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_screen_dot_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:35:41 by katakada          #+#    #+#             */
/*   Updated: 2025/07/27 18:15:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CENTERING_OFFSET 0.5F

static t_vector	calc_diff_by_fixed_interval_sampling(t_scene *scene)
{
	t_vector	shift_diff;
	int			shift_pos_x;
	int			shift_pos_y;
	int			grid_size;

	grid_size = (int)ceilf(sqrtf((float)MAX_FIX_SAMPLING));
	shift_pos_x = scene->sampling.count % grid_size;
	shift_pos_y = scene->sampling.count / grid_size;
	shift_diff.x = (float)shift_pos_x + CENTERING_OFFSET / (float)grid_size;
	shift_diff.y = (float)shift_pos_y + CENTERING_OFFSET / (float)grid_size;
	shift_diff.z = 0.0F;
	return (shift_diff);
}

t_vector	calc_screen_dot_pos(t_scene *scene, int x, int y)
{
	t_vector	dot_pos;
	int			flipped_y;
	t_vector	shift_diff;
	float		sampling_x;
	float		sampling_y;

	flipped_y = scene->screen.height - 1 - y;
	shift_diff = calc_diff_by_fixed_interval_sampling(scene);
	sampling_x = (float)x + shift_diff.x;
	sampling_y = (float)flipped_y + shift_diff.y;
	dot_pos = convert_xy_pos_to_xyz_vector(sampling_x, sampling_y, scene);
	return (dot_pos);
}
