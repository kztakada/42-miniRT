/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_threaded_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:50:06 by katakada          #+#    #+#             */
/*   Updated: 2025/07/24 22:36:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	raytrace_at_dot(t_scene *scene, t_vector dot_pos)
{
	t_color			raytraced_color;
	t_raytracing	rt;

	rt.pov_ray.pos = scene->camera.pos;
	rt.pov_ray.dir = normalize_vector(sub_vectors(dot_pos, rt.pov_ray.pos));
	rt.refract_index = AIR_REFRACT_INDEX;
	raytraced_color = raytracing(scene, &rt, MAX_RECURSION_DEPTH);
	return (raytraced_color);
}

// i[0] is x, i[1] is y, i[2] is dot index
static void	*render_thread(void *data)
{
	t_thread_data	*thread;
	t_screen		*screen;
	t_vector		dot_pos;
	t_color			raytraced_color;
	int				i[3];

	thread = (t_thread_data *)data;
	screen = &thread->scene->screen;
	i[1] = thread->num;
	while (i[1] < (int)screen->height)
	{
		i[0] = 0;
		while (i[0] < (int)screen->width)
		{
			dot_pos = calc_screen_dot_pos(thread->scene, i[0], i[1]);
			i[2] = i[1] * screen->width + i[0];
			raytraced_color = raytrace_at_dot(thread->scene, dot_pos);
			screen->dots[i[2]] = add_colors(screen->dots[i[2]],
					raytraced_color);
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
