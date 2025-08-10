/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:11 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 15:25:32 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_default_scene_common(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->screen.width = WIN_WIDTH;
	scene->screen.height = WIN_HEIGHT;
	scene->sampling.count = 0;
	scene->camera.pos = (t_vector){0.0F, 0.0F, 0.0F};
	scene->camera.dir = (t_vector){0.0F, 0.0F, -1.0F};
	scene->camera.fov = 90;
	scene->bg_color = (t_color){(float)BG_COLOR_R / 255.0F, (float)BG_COLOR_G
		/ 255.0F, (float)BG_COLOR_B / 255.0F};
	scene->ambient.brightness = 1.0F;
	scene->ambient.color = (t_color){1.0F, 1.0F, 1.0F};
	scene->lights = NULL;
	scene->objs = NULL;
}

void	set_local_axes(t_scene *scene)
{
	t_list	*current_obj;
	t_obj	*obj;

	if (!scene || !scene->objs)
		return ;
	current_obj = scene->objs;
	while (current_obj)
	{
		obj = get_obj(current_obj);
		if (obj->material.is_checkerboard || obj->material.has_texture
			|| obj->material.has_bump)
			obj->set_local_xyz(obj, &scene->camera.dir);
		current_obj = current_obj->next;
	}
}

void	setup_scene(t_scene *scene)
{
	t_list	*objs;

	if (!scene)
		return ;
	setup_camera_screen(scene);
	set_local_axes(scene);
	scene->bg_color = scale_color(scene->ambient.brightness, scene->bg_color);
	objs = scene->objs;
	if (!objs)
		return ;
	while (objs)
	{
		get_obj(objs)->material.is_bonus = scene->is_bonus;
		objs = objs->next;
	}
}
