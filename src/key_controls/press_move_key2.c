/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_move_key2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:08:40 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 17:38:35 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_foward(t_vector *pos, t_scene *scene)
{
	t_vector	new_pos;

	if (!scene || !pos)
		return ;
	new_pos = add_vectors(*pos, scale_vector(MOVE_SPEED, scene->camera.dir));
	*pos = new_pos;
}

void	move_backward(t_vector *pos, t_scene *scene)
{
	t_vector	new_pos;

	if (!scene || !pos)
		return ;
	new_pos = sub_vectors(*pos, scale_vector(MOVE_SPEED, scene->camera.dir));
	*pos = new_pos;
}

void	move_left(t_vector *pos, t_scene *scene)
{
	t_vector	new_pos;

	if (!scene || !pos)
		return ;
	new_pos = sub_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(scene->screen.x_per_pixel)));
	*pos = new_pos;
}

void	move_right(t_vector *pos, t_scene *scene)
{
	t_vector	new_pos;

	if (!scene || !pos)
		return ;
	new_pos = add_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(scene->screen.x_per_pixel)));
	*pos = new_pos;
}
