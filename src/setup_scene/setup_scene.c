/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:22:11 by katakada          #+#    #+#             */
/*   Updated: 2025/07/23 15:10:35 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// if the camera direction is almost vertical, we need to handle gimbal lock
static t_bool	should_handle_gimbal(float dir_y)
{
	float	abs_y;

	abs_y = fabsf(dir_y);
	if (abs_y > 1.0F - FLT_EPSILON)
		return (TRUE);
	return (FALSE);
}

static t_vector	calc_screen_x_half(t_scene *scene)
{
	t_vector	x_half;
	t_vector	reference_vector;
	t_vector	normal_x_half;
	float		fov_rad;
	float		screen_half_width;

	fov_rad = (float)scene->camera.fov * ((float)M_PI / 180.0F);
	if (should_handle_gimbal(scene->camera.dir.y))
		reference_vector = (t_vector){0, 0, -1.0F};
	else
		reference_vector = (t_vector){0, 1.0F, 0};
	screen_half_width = tanf(fov_rad / 2.0F);
	normal_x_half = cross_vector(reference_vector, scene->camera.dir);
	normal_x_half = normalize_vector(normal_x_half);
	x_half = scale_vector(FOCAL_FACTOR * screen_half_width, normal_x_half);
	return (x_half);
}

static t_vector	calc_screen_y_half(t_scene *scene)
{
	t_vector	y_half;
	t_vector	normal_y_half;
	float		screen_half_height;
	float		inverse_aspect_ratio;

	inverse_aspect_ratio = (float)scene->screen.height
		/ (float)scene->screen.width;
	normal_y_half = cross_vector(scene->screen.x_half, scene->camera.dir);
	normal_y_half = normalize_vector(normal_y_half);
	screen_half_height = vector_len(scene->screen.x_half)
		* inverse_aspect_ratio;
	y_half = scale_vector(screen_half_height, normal_y_half);
	return (y_half);
}

static void	setup_camera_screen(t_scene *scene)
{
	t_vector	screen_center_pos;
	t_vector	delta_xy;
	t_vector	focal_length;

	scene->screen.x_half = calc_screen_x_half(scene);
	scene->screen.y_half = calc_screen_y_half(scene);
	scene->screen.x_per_pixel = scale_vector(-2.0F / (scene->screen.width - 1),
			scene->screen.x_half);
	scene->screen.y_per_pixel = scale_vector(-2.0F / (scene->screen.height - 1),
			scene->screen.y_half);
	focal_length = scale_vector(FOCAL_FACTOR, scene->camera.dir);
	screen_center_pos = add_vectors(scene->camera.pos, focal_length);
	delta_xy = add_vectors(scene->screen.x_half, scene->screen.y_half);
	scene->screen.pos = add_vectors(screen_center_pos, delta_xy);
}

void	setup_scene(t_scene *scene)
{
	printf("Setting up scene...\n");
	scene->camera.pos_initial = scene->camera.pos;
	scene->camera.dir_initial = scene->camera.dir;
	setup_camera_screen(scene);
}
