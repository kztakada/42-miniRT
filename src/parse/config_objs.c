/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:15:00 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 21:37:05 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_binary_result	config_sphere(char **line_element, t_obj *obj)
{
	if (format_check_sphere(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(obj->shape.sphere.pos), line_element[1]);
	obj->shape.sphere.pos_initial = obj->shape.sphere.pos;
	obj->shape.sphere.diameter = ft_atof(line_element[2]);
	obj->shape.sphere.r2 = 0.0f;
	obj->calc_cross_distance = NULL;
	obj->calc_normal = NULL;
	obj->get_color = NULL;
	obj->print_focused_obj = NULL;
	return (set_material(obj, line_element, 3));
}

t_binary_result	config_plane(char **line_element, t_obj *obj)
{
	if (format_check_plane(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(obj->shape.plane.pos), line_element[1]);
	set_vector(&(obj->shape.plane.dir), line_element[2]);
	if ((obj->shape.plane.dir.x < -1.0f || obj->shape.plane.dir.x > 1.0f)
		|| (obj->shape.plane.dir.y < -1.0f || obj->shape.plane.dir.y > 1.0f)
		|| (obj->shape.plane.dir.z < -1.0f || obj->shape.plane.dir.z > 1.0f))
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	obj->shape.plane.pos_initial = obj->shape.plane.pos;
	obj->shape.plane.dir_initial = obj->shape.plane.dir;
	obj->calc_cross_distance = NULL;
	obj->calc_normal = NULL;
	obj->get_color = NULL;
	obj->print_focused_obj = NULL;
	return (set_material(obj, line_element, 3));
}

t_binary_result	config_cylinder(char **line_element, t_obj *obj)
{
	if (format_check_cylinder(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(obj->shape.cylinder.pos), line_element[1]);
	set_vector(&(obj->shape.cylinder.dir), line_element[2]);
	if ((obj->shape.cylinder.dir.x < -1.0f || obj->shape.cylinder.dir.x > 1.0f)
		|| (obj->shape.cylinder.dir.y < -1.0f || obj->shape.cylinder.dir.y > 1.0f)
		|| (obj->shape.cylinder.dir.z < -1.0f || obj->shape.cylinder.dir.z > 1.0f))
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	obj->shape.cylinder.pos_initial = obj->shape.cylinder.pos;
	obj->shape.cylinder.dir_initial = obj->shape.cylinder.dir;
	obj->shape.cylinder.diameter = ft_atof(line_element[3]);
	obj->shape.cylinder.height = ft_atof(line_element[4]);
	obj->shape.cylinder.r2 = 0.0f;
	obj->shape.cylinder.p1 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cylinder.p2 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cylinder.delta_p = (t_vector){0.0f, 0.0f, 0.0f};
	obj->calc_cross_distance = NULL;
	obj->calc_normal = NULL;
	obj->get_color = NULL;
	obj->print_focused_obj = NULL;
	return (set_material(obj, line_element, 5));
}
