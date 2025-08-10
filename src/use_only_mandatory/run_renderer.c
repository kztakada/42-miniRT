/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:32:34 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 16:36:32 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_console(t_scene_with_mlx *r_scene)
{
	if (!r_scene)
		return ;
	print_rendering_console(r_scene);
}

// i[0] is x, i[1] is y, i[2] is dot index
t_binary_result	run_renderer(t_scene *scene)
{
	t_screen	*screen;
	t_vector	dot_pos;
	t_color		raytraced_color;
	int			i[3];

	screen = &scene->screen;
	i[1] = 0;
	while (i[1] < (int)screen->height)
	{
		i[0] = 0;
		while (i[0] < (int)screen->width)
		{
			dot_pos = calc_screen_dot_pos(scene, i[0], i[1]);
			i[2] = i[1] * screen->width + i[0];
			raytraced_color = raytrace_at_dot(scene, dot_pos);
			screen->dots[i[2]] = add_colors(screen->dots[i[2]],
					raytraced_color);
			i[0]++;
		}
		i[1]++;
	}
	return (SUCCESS);
}
