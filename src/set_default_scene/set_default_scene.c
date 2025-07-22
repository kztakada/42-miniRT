/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:59:23 by katakada          #+#    #+#             */
/*   Updated: 2025/07/22 15:05:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_default_scene(t_scene *scene)
{
	printf("Setting default scene...\n");
	scene->screen.width = WIN_WIDTH;
	scene->screen.height = WIN_HEIGHT;
	scene->screen.qx = (t_vector){1.0f, 0.0f, 0.0f};
	scene->screen.qy = (t_vector){0.0f, 1.0f, 0.0f};
	scene->sampling.count = 1;
	scene->sampling.max_count = MAX_FIX_SAMPLING;
	scene->camera.pos = (t_vector){0.0f, 0.0f, 0.0f};
	scene->camera.dir = (t_vector){0.0f, 0.0f, -1.0f};
	scene->camera.pos_initial = scene->camera.pos;
	scene->camera.dir_initial = scene->camera.dir;
	scene->camera.fov = 90; // Default FOV
	scene->bg_color = (t_color){0.2f, 0.2f, 0.2f};
	// Default background color
	scene->ambient.brightness = 1.0f;
	// Default ambient brightness
	scene->ambient.color = (t_color){1.0f, 1.0f, 1.0f}; // Default ambient color
	scene->lights = NULL;
	scene->objs = NULL;
	for (int i = 0; i < MAX_THREADS; i++)
	{
		scene->thread[i].id = 0;
		scene->thread[i].num = i;
		scene->thread[i].scene = scene;
		scene->thread[i].mlx_img = NULL;
	}
}
