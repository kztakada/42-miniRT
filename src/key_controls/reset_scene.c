/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:38:36 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 13:56:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	reset_camera(t_scene_with_mlx *r_scene)
{
	t_scene	*scene;

	scene = r_scene->scene;
	scene->camera.pos = scene->camera.pos_initial;
	scene->camera.dir = scene->camera.dir_initial;
}

static void	reset_selected_obj(t_scene_with_mlx *r_scene)
{
	if (r_scene->key.selected_obj == NULL)
		return ;
	if (r_scene->key.selected_obj->reset_obj == NULL)
		return ;
	r_scene->key.selected_obj->reset_obj(r_scene->key.selected_obj);
}

static void	reset_selected_light(t_scene_with_mlx *r_scene)
{
	t_light	*selected_light;

	if (r_scene->key.selected_light == NULL)
		return ;
	selected_light = get_light(r_scene->key.selected_light);
	selected_light->pos = selected_light->pos_initial;
	selected_light->brightness = selected_light->brightness_initial;
}

void	reset_selected_mode_target(t_scene_with_mlx *r_scene)
{
	if (r_scene->key.mode == OBJECT_MODE)
		reset_selected_obj(r_scene);
	else if (r_scene->key.mode == LIGHT_MODE)
		reset_selected_light(r_scene);
	else
		reset_camera(r_scene);
	r_scene->key.is_modified = TRUE;
	reset_rendering_scene(r_scene->scene);
}

void	reset_scene_all(t_scene_with_mlx *r_scene)
{
	t_list	*objs;
	t_list	*lights;

	objs = r_scene->key.first_index_obj;
	lights = r_scene->key.first_index_light;
	while (objs)
	{
		if (get_obj(objs)->reset_obj)
			get_obj(objs)->reset_obj(get_obj(objs));
		objs = objs->next;
	}
	while (lights)
	{
		get_light(lights)->pos = get_light(lights)->pos_initial;
		get_light(lights)->brightness = get_light(lights)->brightness_initial;
		lights = lights->next;
	}
	reset_camera(r_scene);
	r_scene->key.is_modified = TRUE;
	reset_rendering_scene(r_scene->scene);
}
