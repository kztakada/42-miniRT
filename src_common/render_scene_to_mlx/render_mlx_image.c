/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mlx_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:46:12 by katakada          #+#    #+#             */
/*   Updated: 2025/07/21 15:49:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rendering_progress(t_scene *scene)
{
	printf("\rRendering progress: %d/%d", scene->sampling.count,
		scene->sampling.max_count);
	fflush(stdout);
}

static void	put_mlx_pixel(t_image *mlx_img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8);
	dst = mlx_img->addr + offset;
	*(unsigned int *)dst = color;
}

void	screen_to_mlx_image(t_image *mlx_img, t_scene *scene)
{
	size_t	x;
	size_t	y;
	size_t	dot_index;
	t_color	avg_color;

	y = 0;
	while (y < scene->screen.height)
	{
		x = 0;
		while (x < scene->screen.width)
		{
			dot_index = y * scene->screen.width + x;
			avg_color = scale_color(1.0F / (float)scene->sampling.count,
					scene->screen.dots[dot_index]);
			put_mlx_pixel(mlx_img, x, y, color_to_int_rgb(avg_color));
			x++;
		}
		y++;
	}
}

void	render_mlx_image(t_scene_with_mlx *r_scene)
{
	t_scene	*scene;

	scene = r_scene->scene;
	if (scene->sampling.count == scene->sampling.max_count)
		return ;
	if (run_threaded_render(r_scene, scene) == FAILURE)
	{
		free_scene_with_mlx(r_scene);
		exit(EXIT_FAILURE);
	}
	scene->sampling.count++;
	print_rendering_progress(scene);
	screen_to_mlx_image(r_scene->mlx_img, scene);
}
