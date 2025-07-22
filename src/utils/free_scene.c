/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:40:14 by katakada          #+#    #+#             */
/*   Updated: 2025/07/20 20:10:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->screen.dots)
		free(scene->screen.dots);
	// Free lights
	ft_lstclear(&scene->lights, free);
	// Free objects
	ft_lstclear(&scene->objs, free);
}

void	free_scene_with_mlx(t_scene_with_mlx *scene_with_mlx)
{
	if (!scene_with_mlx)
		return ;
	if (scene_with_mlx->mlx_img)
	{
		if (scene_with_mlx->mlx_img->img)
			mlx_destroy_image(scene_with_mlx->mlx,
				scene_with_mlx->mlx_img->img);
	}
	if (scene_with_mlx->mlx_win)
		mlx_destroy_window(scene_with_mlx->mlx, scene_with_mlx->mlx_win);
	if (scene_with_mlx->mlx)
	{
		mlx_destroy_display(scene_with_mlx->mlx);
		free(scene_with_mlx->mlx);
	}
	if (scene_with_mlx->scene)
		free_scene(scene_with_mlx->scene);
}
