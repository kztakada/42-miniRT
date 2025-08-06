/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:29:27 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 01:43:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_uv_right(float *rotate_y)
{
	if (!rotate_y)
		return ;
	*rotate_y += UV_ROTATE_ANGLE;
}

void	rotate_uv_left(float *rotate_y)
{
	if (!rotate_y)
		return ;
	*rotate_y -= UV_ROTATE_ANGLE;
}

static void	press_up_down_key(t_scene_with_mlx *r_scene,
		void (*rotate_func)(t_mode_select, t_vector *, t_scene *),
		void (*brighten_func)(float *))
{
	t_scene	*scene;
	t_obj	*selected_obj;

	scene = r_scene->scene;
	if (r_scene->key.mode == CAMERA_MODE)
		rotate_func(CAMERA_MODE, &scene->camera.dir, scene);
	else if (r_scene->key.mode == OBJECT_MODE)
	{
		if (r_scene->key.selected_obj == NULL)
			return ;
		selected_obj = r_scene->key.selected_obj;
		if (selected_obj->get_dir(selected_obj).type != VECTOR_DIR)
			return ;
		rotate_func(OBJECT_MODE, selected_obj->get_dir(selected_obj).dir,
			scene);
	}
	else if (r_scene->key.mode == LIGHT_MODE)
	{
		if (r_scene->key.selected_light == NULL)
			return ;
		brighten_func(&(get_light(r_scene->key.selected_light)->brightness));
	}
	reset_rendering_scene(r_scene->scene);
}

static void	press_left_right_key(t_scene_with_mlx *r_scene,
		void (*rotate_func)(t_mode_select, t_vector *, t_scene *),
		void (*rotate_uv_func)(float *), void (*color_func)(t_color *))
{
	t_scene	*scene;
	t_obj	*selected_obj;

	scene = r_scene->scene;
	if (r_scene->key.mode == CAMERA_MODE)
		rotate_func(CAMERA_MODE, &scene->camera.dir, scene);
	else if (r_scene->key.mode == OBJECT_MODE)
	{
		if (r_scene->key.selected_obj == NULL)
			return ;
		selected_obj = r_scene->key.selected_obj;
		if (selected_obj->get_dir(selected_obj).type == VECTOR_DIR)
			rotate_func(OBJECT_MODE, selected_obj->get_dir(selected_obj).dir,
				scene);
		else if (selected_obj->get_dir(selected_obj).type == UV_DIR)
			rotate_uv_func(selected_obj->get_dir(selected_obj).rotate_y);
	}
	else if (r_scene->key.mode == LIGHT_MODE)
	{
		if (r_scene->key.selected_light == NULL)
			return ;
		color_func(&(get_light(r_scene->key.selected_light)->color));
	}
	reset_rendering_scene(r_scene->scene);
}

void	press_arrow_key(t_scene_with_mlx *r_scene, int keycode)
{
	if (!r_scene)
		return ;
	if (keycode == KEY_LEFT)
		press_left_right_key(r_scene, rotate_left, rotate_uv_left, color_up);
	else if (keycode == KEY_RIGHT)
		press_left_right_key(r_scene, rotate_right, rotate_uv_right,
			color_down);
	else if (keycode == KEY_UP)
		press_up_down_key(r_scene, rotate_up, grighten_up);
	else if (keycode == KEY_DOWN)
		press_up_down_key(r_scene, rotate_down, grighten_down);
	else
		return ;
}
