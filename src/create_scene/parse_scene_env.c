/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:29:01 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 22:45:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	parse_ambient(t_scene *scene, char **line_element,
		t_parse *format_info)
{
	if (format_check_ambient(line_element, format_info) == FAILURE)
		return (FAILURE);
	scene->ambient.brightness = ft_atof(line_element[1]);
	if (scene->ambient.brightness < 0.0f || scene->ambient.brightness > 1.0f)
		return (put_out_format_error(line_element[0], ERR_BRIGHT_ARG));
	if (set_color(&(scene->ambient.color), line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	return (SUCCESS);
}

t_binary_result	parse_camera(t_scene *scene, char **line_element,
		t_parse *format_info)
{
	if (format_check_camera(line_element, format_info) == FAILURE)
		return (FAILURE);
	set_vector(&(scene->camera.pos), line_element[1]);
	set_vector(&(scene->camera.dir), line_element[2]);
	if (is_normal_range(scene->camera.dir) == FALSE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	scene->camera.fov = ft_atoi(line_element[3]);
	if (scene->camera.fov > 180)
		return (put_out_format_error(line_element[0], ERR_FOV_ARG));
	scene->camera.pos_initial = scene->camera.pos;
	scene->camera.dir_initial = scene->camera.dir;
	return (SUCCESS);
}

static t_binary_result	parse_common_light(char **line_element, t_light *light)
{
	set_vector(&(light->pos), line_element[1]);
	light->brightness = ft_atof(line_element[2]);
	if (light->brightness < 0.0f || light->brightness > 1.0f)
		return (put_out_format_error(line_element[0], ERR_BRIGHT_ARG));
	if (line_element[3] != NULL)
	{
		if (set_color(&(light->color), line_element[3]) == FAILURE)
			return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	}
	else
		light->color = (t_color){1.0f, 1.0f, 1.0f};
	light->pos_initial = light->pos;
	light->brightness_initial = light->brightness;
	return (SUCCESS);
}

t_binary_result	parse_light(t_scene *scene, char **line_element,
		t_parse *format_info, t_bool is_bonus)
{
	t_light	*light;
	t_list	*new;

	if (is_bonus)
	{
		if (format_check_lights_bonus(line_element, format_info) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (format_check_light(line_element, format_info) == FAILURE)
			return (FAILURE);
	}
	light = malloc(sizeof(t_light) * 1);
	if (!light)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL));
	ft_bzero(light, sizeof(t_light));
	if (parse_common_light(line_element, light) == FAILURE)
		return (free(light), FAILURE);
	new = ft_lstnew(light);
	if (!new)
		return (free(light), put_out_format_error(line_element[0],
				ERR_MALLOC_FAIL));
	ft_lstadd_back(&(scene->lights), new);
	return (SUCCESS);
}
