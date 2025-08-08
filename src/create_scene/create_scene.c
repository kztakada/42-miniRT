/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:27:01 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 17:08:22 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	debug_print(t_scene *scene)
// {
// 	t_light	*light;
// 	t_obj	*obj;

// 	printf("\nAmbient----------------------------\n");
// 	printf("brightness: %f\n", scene->ambient.brightness);
// 	printf("color: r:%f g:%f b:%f\n", scene->ambient.color.r,
// scene->ambient.color.g, scene->ambient.color.b);

// 	printf("\nCamera----------------------------\n");
// 	printf("pos: x:%f y:%f z:%f\n", scene->camera.pos.x, scene->camera.pos.y,
// scene->camera.pos.z);
// 	printf("dir: x:%f y:%f z:%f\n", scene->camera.dir.x, scene->camera.dir.y,
// scene->camera.dir.z);
// 	printf("fov: %zu\n", scene->camera.fov);

// 	printf("\nLights----------------------------\n");
// 	light = scene->lights->content;
// 	printf("pos: x:%f y:%f z:%f\n", light->pos.x, light->pos.y, light->pos.z);
// 	printf("brightness: %f\n", light->brightness);
// 	printf("color: r:%f g:%f b:%f\n", light->color.r, light->color.g,
// light->color.b);

// 	printf("\nObjs----------------------------\n");
// printf("\nplane---------------\n");
// obj = scene->objs->content;
// printf("pos: x:%f y:%f z:%f\n", obj->shape.plane.pos.x,
// obj->shape.plane.pos.y, obj->shape.plane.pos.z);
// printf("dir: x:%f y:%f z:%f\n", obj->shape.plane.dir.x,
// obj->shape.plane.dir.y, obj->shape.plane.dir.z);
// printf("color: r:%f g:%f b:%f\n", obj->material.color.r,
// obj->material.color.g, obj->material.color.b);
// printf("mirror:%f specn:%f speckv:%f\n", obj->material.mirror,
// obj->material.specn, obj->material.speckv);
// printf("refract:%f\n", obj->material.refract);
// if (obj->material.is_checkerboard == TRUE)
// 	printf("checker_board: TRUE\n");
// if (obj->material.has_texture == TRUE)
// 	printf("has_texture: TRUE\n");
// if (obj->material.has_bump == TRUE)
// 	printf("has_bump: TRUE\n");

// printf("\nsphere---------------\n");
// obj = scene->objs->content;
// printf("pos: x:%f y:%f z:%f\n", obj->shape.sphere.pos.x,
// obj->shape.sphere.pos.y, obj->shape.sphere.pos.z);
// printf("diameter: %f\n", obj->shape.sphere.diameter);
// printf("color: r:%f g:%f b:%f\n", obj->material.color.r,
// obj->material.color.g, obj->material.color.b);
// printf("mirror:%f specn:%f speckv:%f\n", obj->material.mirror,
// obj->material.specn, obj->material.speckv);
// printf("refract:%f\n", obj->material.refract);

// printf("\ncylinder---------------\n");
// obj = scene->objs->next->next->content;
// printf("pos: x:%f y:%f z:%f\n", obj->shape.cylinder.pos.x,
// obj->shape.cylinder.pos.y, obj->shape.cylinder.pos.z);
// printf("dir: x:%f y:%f z:%f\n", obj->shape.cylinder.dir.x,
// obj->shape.cylinder.dir.y, obj->shape.cylinder.dir.z);
// printf("diameter: %f\n", obj->shape.cylinder.diameter);
// printf("height: %f\n", obj->shape.cylinder.height);
// printf("color: r:%f g:%f b:%f\n", obj->material.color.r,
// obj->material.color.g, obj->material.color.b);
// }

void	parse_init(t_parse *format_info)
{
	format_info->ambient = FALSE;
	format_info->camera = FALSE;
	format_info->large_light = FALSE;
	format_info->light_count = 0;
}

t_binary_result	parse_scene(t_scene *scene, const char *file_path)
{
	int		rt_fd;
	char	*line;
	t_parse	format_info;

	parse_init(&format_info);
	rt_fd = open(file_path, O_RDONLY);
	while (TRUE)
	{
		line = get_next_line(rt_fd);
		if (!line)
			break ;
		if (parse_one_line_on_scene(scene, line, &format_info) == FAILURE)
		{
			free(line);
			close(rt_fd);
			return (FAILURE);
		}
		free(line);
	}
	// debug_print(scene); // for debug
	close(rt_fd);
	return (SUCCESS);
}

t_binary_result	create_scene(t_scene *scene, const char *file_path)
{
	scene->screen.dots = malloc(sizeof(t_color) * scene->screen.width
			* scene->screen.height);
	if (scene->screen.dots == NULL)
		return (put_out_failure(ERR_MALLOC_FAIL));
	ft_bzero(scene->screen.dots, sizeof(t_color) * scene->screen.width
		* scene->screen.height);
	if (parse_scene(scene, file_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
