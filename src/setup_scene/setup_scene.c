/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:11 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 14:37:59 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_scene(t_scene *scene)
{
	printf("Setting up scene...\n");
	scene->camera.pos_initial = scene->camera.pos;
	scene->camera.dir_initial = scene->camera.dir;
	setup_camera_screen(scene);
}
