/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_screen_dot_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:35:41 by katakada          #+#    #+#             */
/*   Updated: 2025/07/22 22:01:33 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CENTERING_OFFSET 0.5F

/*
sub_grid: (gap_x, gap_y, size_of_one_side_of_grid)
sub_grid is a grid that divides 1x1 pixels into subdivisions of sampling numbers.
*/
t_vector	calc_screen_dot_pos(t_scene *scene, int x, int y)
{
	t_vector	dot_pos;
	t_vector	diff_v[2];
	int			flipped_y;
	float		fix_f[2];
	int			sub_grid[3];

	flipped_y = scene->screen.height - 1 - y;
	sub_grid[2] = (int)ceilf(sqrtf((float)MAX_FIX_SAMPLING));
	sub_grid[0] = scene->sampling.count % sub_grid[2];
	sub_grid[1] = scene->sampling.count / sub_grid[2];
	fix_f[0] = ((float)sub_grid[0] + CENTERING_OFFSET) / (float)sub_grid[2];
	fix_f[1] = ((float)sub_grid[1] + CENTERING_OFFSET) / (float)sub_grid[2];
	diff_v[0] = scale_vector((float)x + fix_f[0], scene->screen.x_per_pixel);
	diff_v[1] = scale_vector((float)flipped_y + fix_f[1],
			scene->screen.y_per_pixel);
	dot_pos = add_vectors(scene->screen.pos, diff_v[0]);
	dot_pos = add_vectors(dot_pos, diff_v[1]);
	return (dot_pos);
}
