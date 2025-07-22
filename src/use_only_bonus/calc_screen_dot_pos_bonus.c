/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_screen_dot_pos_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:34:33 by katakada          #+#    #+#             */
/*   Updated: 2025/07/21 20:41:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_rand_float(void)
{
	float	result;

	result = (float)rand() / ((float)RAND_MAX + 1.0F);
	if (result >= 1.0F)
		result = 1.0F - FLT_EPSILON;
	return (result);
}

t_vector	calc_screen_dot_pos(t_scene *scene, int x, int y)
{
	t_vector	dot_pos;
	t_vector	diff_x;
	t_vector	diff_y;
	int			flipped_y;
	float		rand_f[2];

	flipped_y = scene->screen.height - 1 - y;
	rand_f[0] = get_rand_float();
	rand_f[1] = get_rand_float();
	diff_x = scale_vector((float)x + rand_f[0], scene->screen.qx);
	diff_y = scale_vector((float)flipped_y + rand_f[1], scene->screen.qy);
	dot_pos = add_vectors(scene->screen.pos, diff_x);
	dot_pos = add_vectors(dot_pos, diff_y);
	return (dot_pos);
}
