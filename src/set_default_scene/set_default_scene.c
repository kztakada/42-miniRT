/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:59:23 by katakada          #+#    #+#             */
/*   Updated: 2025/07/25 23:29:49 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_default_scene(t_scene *scene)
{
	scene->screen.width = WIN_WIDTH;
	scene->screen.height = WIN_HEIGHT;
	scene->sampling.count = 0;
	scene->sampling.max_count = MAX_FIX_SAMPLING;
	scene->camera.pos = (t_vector){0.0F, 0.0F, 0.0F};
	scene->camera.dir = (t_vector){0.0F, 0.0F, -1.0F};
	scene->camera.fov = 90;
	scene->bg_color = (t_color){0.2F, 0.2F, 0.2F};
	scene->ambient.brightness = 1.0F;
	scene->ambient.color = (t_color){1.0F, 1.0F, 1.0F};
	scene->lights = NULL;
	scene->objs = NULL;
}
