/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_objs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:28:02 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/02 18:02:36 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	config_triangle(char **line_element, t_obj *obj)
{
	(void)line_element;
	(void)obj;
	return (SUCCESS);
}

t_binary_result	config_torus(char **line_element, t_obj *obj)
{
	(void)line_element;
	(void)obj;
	return (SUCCESS);
}

t_binary_result	config_cone(char **line_element, t_obj *obj)
{
	int result_status;

	if (format_check_cone(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(obj->shape.cone.pos), line_element[1]);
	set_vector(&(obj->shape.cone.dir), line_element[2]);
	if ((obj->shape.cone.dir.x < -1.0f || obj->shape.cone.dir.x > 1.0f)
		|| (obj->shape.cone.dir.y < -1.0f || obj->shape.cone.dir.y > 1.0f)
		|| (obj->shape.cone.dir.z < -1.0f || obj->shape.cone.dir.z > 1.0f))
		return (FAILURE);
	obj->shape.cone.pos_initial = obj->shape.cone.pos;
	obj->shape.cone.dir_initial = obj->shape.cone.dir;
	obj->shape.cone.h = ft_atof(line_element[3]);
	obj->shape.cone.h2 = ft_atof(line_element[4]);
	obj->shape.cone.angle = ft_atof(line_element[5]);
	obj->shape.cone.cos2 = 0.0f;
	obj->shape.cone.c1 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cone.c2 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cone.r1 = 0.0f;
	obj->shape.cone.r2 = 0.0f;
	obj->has_volume = FALSE;
	obj->calc_obj_hit = calc_cone_obj_hit;
	obj->calc_normal = calc_cone_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_cone;
	obj->get_pos = get_cone_pos;
	obj->get_dir = get_cone_dir;
	result_status = set_material(obj, line_element, 6);
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_cone_bump_normal;
	return (result_status);
}

t_binary_result	config_objs(t_scene *scene, char **line_element)
{
	int		result_status;
	t_obj	*obj;
	t_list	*new;

	obj = malloc(sizeof(t_obj) * 1);
	if (!obj)
		return (FAILURE);
	obj->ex = (t_vector){0.0f, 0.0f, 0.0f};
	obj->ey = (t_vector){0.0f, 0.0f, 0.0f};
	obj->ez = (t_vector){0.0f, 0.0f, 0.0f};
	if (ft_strcmp(line_element[0], "sp") == 0)
		result_status = config_sphere(line_element, obj);
	else if (ft_strcmp(line_element[0], "pl") == 0)
		result_status = config_plane(line_element, obj);
	else if (ft_strcmp(line_element[0], "cy") == 0)
		result_status = config_cylinder(line_element, obj);
	else if (ft_strcmp(line_element[0], "co") == 0)
		result_status = config_cone(line_element, obj);
	else
		return (put_out_format_error(line_element[0], ERR_NO_IDENT),
			free(obj), FAILURE);
	new = ft_lstnew(obj);
	if (!new)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL),
			free(obj), FAILURE);
	ft_lstadd_back(&(scene->objs), new);
	return (result_status);
}
