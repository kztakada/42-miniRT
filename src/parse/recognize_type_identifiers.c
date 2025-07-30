/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_type_identifiers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:55:50 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 22:24:54 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	config_ambient(t_scene *scene, char **line_element)
{
	if (format_check_ambient(line_element) == FAILURE)
		return (FAILURE);
	scene->ambient.brightness = ft_atof(line_element[1]);
	if (scene->ambient.brightness < 0.0f && scene->ambient.brightness > 1.0f)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	if (set_color(&(scene->ambient.color), line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	return (SUCCESS);
}

static t_binary_result	config_camera(t_scene *scene, char **line_element)
{
	if (format_check_camera(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(scene->camera.pos), line_element[1]);
	set_vector(&(scene->camera.dir), line_element[2]);
	if ((scene->camera.dir.x < -1.0f || scene->camera.dir.x > 1.0f)
		|| (scene->camera.dir.y < -1.0f || scene->camera.dir.y > 1.0f)
		|| (scene->camera.dir.z < -1.0f || scene->camera.dir.z > 1.0f))
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	scene->camera.fov = ft_atoi(line_element[3]);
	if (scene->camera.fov > 180)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	scene->camera.pos_initial = scene->camera.pos;
	scene->camera.dir_initial = scene->camera.dir;
	return (SUCCESS);
}

static t_binary_result	config_light(t_scene *scene, char **line_element)
{
	t_light	*light;

	if (format_check_light(line_element) == FAILURE)
		return (FAILURE);
	light = malloc(sizeof(t_light) * 1);
	if (!light)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL));
	set_vector(&(light->pos), line_element[1]);
	light->brightness = ft_atof(line_element[2]);
	if (light->brightness < 0.0f && light->brightness > 1.0f)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	if (set_color(&(light->color), line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	scene->lights = ft_lstnew(light);
	if (!scene->lights)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL));
	return (SUCCESS);
}

t_binary_result	recognize_type_identifiers(t_scene *scene, char *line)
{
	char	**line_element;
	int		result_status;

	line_element = ft_split_with_blank(line);
	if (!line_element)
		return (put_out_failure(ERR_MALLOC_FAIL));
	if (!line_element[0])
		return (ft_free_char2(line_element), SUCCESS);
	if (ft_strcmp(line_element[0], "A") == 0)
		result_status = config_ambient(scene, line_element);
	else if (ft_strcmp(line_element[0], "C") == 0)
		result_status = config_camera(scene, line_element);
	else if (ft_strcmp(line_element[0], "L") == 0)
		result_status = config_light(scene, line_element);
	else
		result_status = config_objs(scene, line_element);
	ft_free_char2(line_element);
	return (result_status);
}
