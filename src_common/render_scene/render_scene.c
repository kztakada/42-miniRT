/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:48:53 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 14:19:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	init_mlx(t_scene_for_mlx *mlx_scene, t_image *mlx_img,
		t_scene *scene)
{
	mlx_scene->mlx_img = mlx_img;
	mlx_scene->scene = scene;
	mlx_scene->mlx = mlx_init();
	if (mlx_scene->mlx == NULL)
		return (FAILURE);
	mlx_scene->mlx_win = mlx_new_window(mlx_scene->mlx, scene->screen.width,
			scene->screen.height, WIN_TITLE);
	if (mlx_scene->mlx_win == NULL)
		return (FAILURE);
	mlx_img->img = mlx_new_image(mlx_scene->mlx, scene->screen.width,
			scene->screen.height);
	if (mlx_img->img == NULL)
		return (FAILURE);
	mlx_img->addr = mlx_get_data_addr(mlx_img->img, &mlx_img->bits_per_pixel,
			&mlx_img->line_length, &mlx_img->endian);
	mlx_img->width = scene->screen.width;
	mlx_img->height = scene->screen.height;
	ft_bzero(mlx_img->addr, mlx_img->width * mlx_img->height
		* (mlx_img->bits_per_pixel / 8));
	return (SUCCESS);
}

t_binary_result	render_scene(t_scene *scene)
{
	t_scene_for_mlx	mlx_scene;
	t_image			mlx_img;

	printf("Rendering scene...\n");
	if (init_mlx(&mlx_scene, &mlx_img, scene) == FAILURE)
	{
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd(ERR_MLX_INIT, STDERR_FILENO);
		return (FAILURE);
	}
	mlx_destroy_image(mlx_scene.mlx, mlx_img.img);
	mlx_destroy_window(mlx_scene.mlx, mlx_scene.mlx_win);
	return (SUCCESS);
}
