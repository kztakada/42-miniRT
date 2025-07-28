/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_move_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:29:32 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 16:41:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_up(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = add_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(r_scene->scene->screen.y_per_pixel)));
	*pos = new_pos;
}

static void	move_down(t_vector *pos, t_scene_with_mlx *r_scene)
{
	t_vector	new_pos;

	if (!r_scene || !pos)
		return ;
	new_pos = sub_vectors(*pos, scale_vector(MOVE_SPEED,
				normalize_vector(r_scene->scene->screen.y_per_pixel)));
	*pos = new_pos;
}

static void	press_move_key_any(t_scene_with_mlx *r_scene,
		void (*move_func)(t_vector *, t_scene_with_mlx *))
{
	t_scene	*scene;
	t_obj	*selected_obj;

	if (!r_scene)
		return ;
	scene = r_scene->scene;
	if (r_scene->key.mode == CAMERA_MODE)
	{
		move_func(&scene->camera.pos, r_scene);
		set_screen_pos(scene);
	}
	else if (r_scene->key.mode == OBJECT_MODE)
	{
		if (r_scene->key.selected_obj == NULL)
			return ;
		selected_obj = r_scene->key.selected_obj;
		move_func(selected_obj->get_pos(selected_obj), r_scene);
	}
	else if (r_scene->key.mode == LIGHT_MODE)
	{
		if (r_scene->key.selected_light == NULL)
			return ;
		move_func(&(get_light(r_scene->key.selected_light)->pos), r_scene);
	}
	reset_rendering_scene(r_scene->scene);
}

void	press_move_key(t_scene_with_mlx *r_scene, int keycode)
{
	if (keycode == KEY_W)
		press_move_key_any(r_scene, move_foward);
	else if (keycode == KEY_S)
		press_move_key_any(r_scene, move_backward);
	else if (keycode == KEY_A)
		press_move_key_any(r_scene, move_left);
	else if (keycode == KEY_D)
		press_move_key_any(r_scene, move_right);
	else if (keycode == KEY_Q)
		press_move_key_any(r_scene, move_down);
	else if (keycode == KEY_E)
		press_move_key_any(r_scene, move_up);
	else
		return ;
}
