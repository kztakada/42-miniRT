/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_move_key2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:08:40 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 15:10:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_foward(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = add_vectors(*pos, scale_vector(MOVE_SPEED,
				r_scene->scene->camera.dir));
	*pos = new_pos;
}

void	move_backward(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = sub_vectors(*pos, scale_vector(MOVE_SPEED,
				r_scene->scene->camera.dir));
	*pos = new_pos;
}

void	move_left(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = sub_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(r_scene->scene->screen.x_per_pixel)));
	*pos = new_pos;
}

void	move_right(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = add_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(r_scene->scene->screen.x_per_pixel)));
	*pos = new_pos;
}
