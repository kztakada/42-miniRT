/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mlx_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:46:12 by katakada          #+#    #+#             */
/*   Updated: 2025/07/31 19:08:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	convert_xy_pos_to_xyz_vector(float x, float y, t_scene *scene)
{
	t_vector	dot_pos;
	t_vector	diff_x;
	t_vector	diff_y;

	if (x < 0 || y < 0 || x >= scene->screen.width || y >= scene->screen.height)
	{
		dot_pos = (t_vector){0.0F, 0.0F, 0.0F};
		return (dot_pos);
	}
	diff_x = scale_vector(x, scene->screen.x_per_pixel);
	diff_y = scale_vector(y, scene->screen.y_per_pixel);
	dot_pos = add_vectors(scene->screen.pos, diff_x);
	dot_pos = add_vectors(dot_pos, diff_y);
	return (dot_pos);
}

static void	put_mlx_pixel(t_image *mlx_img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (!mlx_img || !mlx_img->addr || x < 0 || y < 0)
		return ;
	offset = y * mlx_img->line_length + x * (mlx_img->bits_per_pixel / 8);
	if (offset < 0 || offset >= (int)mlx_img->line_length
		* (int)mlx_img->height)
		return ;
	dst = mlx_img->addr + offset;
	*(unsigned int *)dst = color;
}

static void	screen_to_mlx_image(t_image *mlx_img, t_scene *scene)
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

	if (!r_scene || !r_scene->scene)
		return ;
	scene = r_scene->scene;
	if (scene->sampling.count == scene->sampling.max_count)
		return ;
	if (run_renderer(scene) == FAILURE)
	{
		free_scene_with_mlx(r_scene);
		exit(EXIT_FAILURE);
	}
	scene->sampling.count++;
	print_rendering_console(r_scene);
	if (!r_scene || !r_scene->mlx_img)
		return ;
	screen_to_mlx_image(r_scene->mlx_img, scene);
}
