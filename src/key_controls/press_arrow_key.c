/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:29:27 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 18:59:29 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	grighten_up(float *brightness)
{
	if (!brightness)
		return ;
	*brightness += BRIGHTNESS_STEP;
	if (*brightness > 1.0F)
		*brightness = 1.0F;
	if (*brightness < 0.0F)
		*brightness = 0.0F;
}

static void	grighten_down(float *brightness)
{
	if (!brightness)
		return ;
	*brightness -= BRIGHTNESS_STEP;
	if (*brightness > 1.0F)
		*brightness = 1.0F;
	if (*brightness < 0.0F)
		*brightness = 0.0F;
}

static void	press_up_down_key(t_scene_with_mlx *r_scene,
		void (*rotate_func)(t_vector *, t_scene *),
		void (*brighten_func)(float *))
{
	t_scene	*scene;
	t_obj	*selected_obj;

	if (!r_scene)
		return ;
	scene = r_scene->scene;
	if (r_scene->key.mode == CAMERA_MODE)
	{
		rotate_func(&scene->camera.dir, scene);
		setup_camera_screen(scene);
	}
	else if (r_scene->key.mode == OBJECT_MODE)
	{
		if (r_scene->key.selected_obj == NULL)
			return ;
		selected_obj = r_scene->key.selected_obj;
		rotate_func(selected_obj->get_dir(selected_obj), scene);
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
		void (*rotate_func)(t_vector *, t_scene *),
		void (*color_func)(t_color *))
{
	t_scene	*scene;
	t_obj	*selected_obj;

	if (!r_scene)
		return ;
	scene = r_scene->scene;
	if (r_scene->key.mode == CAMERA_MODE)
	{
		rotate_func(&scene->camera.dir, scene);
		setup_camera_screen(scene);
	}
	else if (r_scene->key.mode == OBJECT_MODE)
	{
		if (r_scene->key.selected_obj == NULL)
			return ;
		selected_obj = r_scene->key.selected_obj;
		rotate_func(selected_obj->get_dir(selected_obj), scene);
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
	if (keycode == KEY_LEFT)
		press_left_right_key(r_scene, rotate_left, color_up);
	else if (keycode == KEY_RIGHT)
		press_left_right_key(r_scene, rotate_right, color_down);
	else if (keycode == KEY_UP)
		press_up_down_key(r_scene, rotate_up, grighten_up);
	else if (keycode == KEY_DOWN)
		press_up_down_key(r_scene, rotate_down, grighten_down);
	else
		return ;
}
