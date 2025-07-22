/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threaded_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:50:06 by katakada          #+#    #+#             */
/*   Updated: 2025/07/22 15:16:56 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_raytracing(t_color *original_color, t_scene *scene,
		t_ray *render_ray)
{
	t_color	raytraced_color;

	raytraced_color = raytracing(scene, render_ray, MAX_RECURSION_DEPTH);
	*original_color = add_colors(*original_color, raytraced_color);
}

static void	*render_thread(void *data)
{
	t_thread_data	*thread;
	t_screen		*screen;
	t_ray			render_ray;
	t_vector		dot_pos;
	int				i[3];

	thread = (t_thread_data *)data;
	screen = &thread->scene->screen;
	render_ray.pos = thread->scene->camera.pos;
	i[1] = thread->num;
	while (i[1] < (int)screen->height)
	{
		i[0] = 0;
		while (i[0] < (int)screen->width)
		{
			dot_pos = calc_screen_dot_pos(thread->scene, i[0], i[1]);
			render_ray.dir = sub_vectors(dot_pos, render_ray.pos);
			render_ray.dir = normalize_vector(render_ray.dir);
			i[2] = i[1] * screen->width + i[0];
			add_raytracing(&(screen->dots[i[2]]), thread->scene, &render_ray);
			i[0]++;
		}
		i[1] += MAX_THREADS;
	}
	return (NULL);
}

t_binary_result	run_threaded_render(t_scene_with_mlx *r_scene, t_scene *scene)
{
	int				i;
	t_binary_result	result;

	result = SUCCESS;
	i = 0;
	while (i < MAX_THREADS)
	{
		scene->thread[i].mlx_img = r_scene->mlx_img;
		if (pthread_create(&(scene->thread[i].id), NULL, render_thread,
				&(scene->thread[i])) != 0)
		{
			result = put_out_failure(ERR_CREATE_TH);
			break ;
		}
		i++;
	}
	while (i > 0)
	{
		if (pthread_join(scene->thread[i - 1].id, NULL) != 0)
			result = put_out_failure(ERR_JOIN_TH);
		i--;
	}
	return (result);
}
