/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:59:23 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 20:26:39 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_default_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->screen.width = WIN_WIDTH;
	scene->screen.height = WIN_HEIGHT;
	scene->sampling.count = 0;
	scene->sampling.max_count = MAX_FIX_SAMPLING;
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
