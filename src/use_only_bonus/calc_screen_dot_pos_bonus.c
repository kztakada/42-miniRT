/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_screen_dot_pos_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:34:33 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 15:29:16 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	get_rand_float(void)
{
	float	result;

	result = (float)rand() / ((float)RAND_MAX + 1.0F);
	if (result >= 1.0F)
		result = 1.0F - FLT_EPSILON;
	return (result);
}

static t_vector	calc_diff_by_random_sampling(void)
{
	t_vector	shift_diff;
	float		rand_f[2];

	rand_f[0] = get_rand_float();
	rand_f[1] = get_rand_float();
	shift_diff.x = rand_f[0];
	shift_diff.y = rand_f[1];
	shift_diff.z = 0.0F;
	return (shift_diff);
}

t_vector	calc_screen_dot_pos(t_scene *scene, int x, int y)
{
	t_vector	dot_pos;
	t_vector	shift_diff;
	int			flipped_y;
	float		sampling_x;
	float		sampling_y;

	flipped_y = scene->screen.height - 1 - y;
	shift_diff = calc_diff_by_random_sampling();
	sampling_x = (float)x + shift_diff.x;
	sampling_y = (float)flipped_y + shift_diff.y;
	dot_pos = convert_xy_pos_to_xyz_vector(sampling_x, sampling_y, scene);
	return (dot_pos);
}
