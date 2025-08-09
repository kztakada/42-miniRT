/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene_rt_format.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:13:59 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 16:26:29 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_a_c_rt_format(t_scene *scene)
{
	printf("A %f", scene->ambient.brightness);
	print_rgb_color(scene->ambient.color);
	printf("\nC %f,%f,%f %f,%f,%f %d\n", scene->camera.pos.x,
		scene->camera.pos.y, scene->camera.pos.z, scene->camera.dir.x,
		scene->camera.dir.y, scene->camera.dir.z, (int)scene->camera.fov);
}

static void	print_light_rt_format(t_light *light, char *type, t_bool is_bonus)
{
	if (!light)
		return ;
	printf("%s ", type);
	printf("%f,%f,%f %f", light->pos.x, light->pos.y, light->pos.z,
		light->brightness);
	if (is_bonus)
		print_rgb_color(light->color);
	else
		printf(" 255,255,255");
	printf("\n");
}

static void	print_scene_rt_format(t_scene_with_mlx *r_scene)
{
	t_list	*objs;
	t_list	*lights;
	t_bool	is_bonus;

	objs = r_scene->key.first_index_obj;
	lights = r_scene->key.first_index_light;
	is_bonus = r_scene->scene->is_bonus;
	print_a_c_rt_format(r_scene->scene);
	if (ft_lstsize(r_scene->key.first_index_light) > 1 && is_bonus)
	{
		while (lights)
		{
			print_light_rt_format(get_light(lights), "lt", is_bonus);
			lights = lights->next;
		}
	}
	else
		print_light_rt_format(get_light(lights), "L", is_bonus);
	while (objs)
	{
		if (get_obj(objs)->print_rt)
			get_obj(objs)->print_rt(get_obj(objs));
		objs = objs->next;
	}
}

void	toggle_console(t_scene_with_mlx *r_scene)
{
	if (r_scene == NULL)
		return ;
	if (r_scene->key.is_console == TRUE)
	{
		r_scene->key.is_console = FALSE;
		printf("\033[2J\033[H");
		printf("\033[0m");
		if (r_scene->scene == NULL)
			return ;
		print_scene_rt_format(r_scene);
	}
	else
	{
		r_scene->key.is_console = TRUE;
		r_scene->key.is_modified = TRUE;
		printf("\033[2J\033[H");
		print_console(r_scene);
	}
}
