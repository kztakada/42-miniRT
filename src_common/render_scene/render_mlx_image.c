/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mlx_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:46:12 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 19:03:59 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rendering_progress(t_scene *scene)
{
	printf("\rRendering progress: %d/%d", scene->sampling.count,
		scene->sampling.max_count);
	fflush(stdout);
}

void	render_mlx_image(t_scene_with_mlx *r_scene)
{
	t_scene	*scene;

	scene = r_scene->scene;
	if (scene->sampling.count == scene->sampling.max_count)
		return ;
	// if (exec_multithread_renderer(r_scene, scene) == FAILURE)
	// {
	// 	free_scene_with_mlx(r_scene);
	// 	exit(EXIT_FAILURE);
	// }
	scene->sampling.count++;
	print_rendering_progress(scene);
}
