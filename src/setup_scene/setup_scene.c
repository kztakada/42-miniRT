/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:11 by katakada          #+#    #+#             */
/*   Updated: 2025/08/03 19:48:43 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	printf("Setting up scene...\n");
	setup_camera_screen(scene);
	set_local_axes(scene);
}
