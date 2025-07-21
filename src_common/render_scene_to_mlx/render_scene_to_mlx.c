/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_to_mlx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:07:56 by katakada          #+#    #+#             */
/*   Updated: 2025/07/21 16:07:57 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	init_mlx(t_scene_with_mlx *r_scene, t_image *mlx_img,
		t_scene *scene)
{
	r_scene->mlx_img = mlx_img;
	r_scene->scene = scene;
	r_scene->mlx = mlx_init();
	if (r_scene->mlx == NULL)
		return (FAILURE);
	r_scene->mlx_win = mlx_new_window(r_scene->mlx, scene->screen.width,
			scene->screen.height, WIN_TITLE);
	if (r_scene->mlx_win == NULL)
		return (free_scene_with_mlx(r_scene), FAILURE);
	mlx_img->img = mlx_new_image(r_scene->mlx, scene->screen.width,
			scene->screen.height);
	if (mlx_img->img == NULL)
		return (free_scene_with_mlx(r_scene), FAILURE);
	mlx_img->addr = mlx_get_data_addr(mlx_img->img, &mlx_img->bits_per_pixel,
			&mlx_img->line_length, &mlx_img->endian);
	mlx_img->width = scene->screen.width;
	mlx_img->height = scene->screen.height;
	ft_bzero(mlx_img->addr, mlx_img->width * mlx_img->height
		* (mlx_img->bits_per_pixel / 8));
	return (SUCCESS);
}

static int	render_loop(void *data)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)data;
	render_mlx_image(r_scene);
	mlx_put_image_to_window(r_scene->mlx, r_scene->mlx_win,
		r_scene->mlx_img->img, 0, 0);
	return (0);
}

t_binary_result	render_scene_to_mlx(t_scene *scene)
{
	t_scene_with_mlx	r_scene;
	t_image				mlx_img;

	printf("Rendering scene...\n");
	if (init_mlx(&r_scene, &mlx_img, scene) == FAILURE)
	{
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd(ERR_MLX_INIT, STDERR_FILENO);
		return (FAILURE);
	}
	mlx_put_image_to_window(r_scene.mlx, r_scene.mlx_win, mlx_img.img, 0, 0);
	set_key_controls(&r_scene);
	mlx_loop_hook(r_scene.mlx, render_loop, &r_scene);
	mlx_loop(r_scene.mlx);
	free_scene_with_mlx(&r_scene);
	return (SUCCESS);
}
