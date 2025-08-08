/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rt_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:16:48 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 01:17:07 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rgb_color_info(t_color color)
{
	printf("  Color: (%d, %d, %d)\n", (int)(256.0F * clamp_color(color.r, 0.0F,
				0.999F)), (int)(256.0F * clamp_color(color.g, 0.0F, 0.999F)),
		(int)(256.0F * clamp_color(color.b, 0.0F, 0.999F)));
}

void	print_rgb_color(t_color color)
{
	printf(" %d,%d,%d", (int)(256.0F * clamp_color(color.r, 0.0F, 0.999F)),
		(int)(256.0F * clamp_color(color.g, 0.0F, 0.999F)), (int)(256.0F
			* clamp_color(color.b, 0.0F, 0.999F)));
}

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

void	print_scene_rt_format(t_scene_with_mlx *r_scene, t_bool set_print)
{
	t_list			*objs;
	t_list			*lights;
	t_bool			is_bonus;
	static t_bool	first_call = FALSE;

	if (set_print)
		first_call = !first_call;
	if (first_call == FALSE)
		return ;
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
