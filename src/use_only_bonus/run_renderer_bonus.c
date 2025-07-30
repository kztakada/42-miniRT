/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_renderer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:34:47 by katakada          #+#    #+#             */
/*   Updated: 2025/07/25 23:58:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "thread.h"

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

static t_binary_result	run_threaded_render(t_thread_data *threads)
{
	int				i;
	t_binary_result	result;

	result = SUCCESS;
	i = 0;
	while (i < MAX_THREADS)
	{
		if (pthread_create(&(threads[i].id), NULL, render_thread,
				&(threads[i])) != 0)
		{
			result = put_out_failure(ERR_CREATE_TH);
			break ;
		}
		i++;
	}
	while (i > 0)
	{
		if (pthread_join(threads[i - 1].id, NULL) != 0)
			result = put_out_failure(ERR_JOIN_TH);
		i--;
	}
	return (result);
}

t_binary_result	run_renderer(t_scene *scene)
{
	t_thread_data	threads[MAX_THREADS];
	int				i;

	i = 0;
	while (i < MAX_THREADS)
	{
		threads[i].id = 0;
		threads[i].num = i;
		threads[i].scene = scene;
		i++;
	}
	return (run_threaded_render(threads));
}
