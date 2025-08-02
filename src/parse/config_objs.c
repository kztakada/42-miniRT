/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:15:00 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/02 17:20:00 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_binary_result	config_sphere(char **line_element, t_obj *obj)
{
	int	result_status;

	if (format_check_sphere(line_element) == FAILURE)
		return (FAILURE);
	set_vector(&(obj->shape.sphere.pos), line_element[1]);
	obj->shape.sphere.pos_initial = obj->shape.sphere.pos;
	obj->shape.sphere.diameter = ft_atof(line_element[2]);
	obj->shape.sphere.radius_pow2 = obj->shape.sphere.diameter * obj->shape.sphere.diameter * 0.25f;
	obj->has_volume = TRUE;
	obj->calc_obj_hit = calc_sphere_obj_hit;
	obj->calc_normal = calc_sphere_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_sphere;
	obj->get_pos = get_sphere_pos;
	obj->get_dir = get_sphere_dir;
	result_status = set_material(obj, line_element, 3);
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_sphere_bump_normal;
	return (result_status);
}

t_binary_result	config_plane(char **line_element, t_obj *obj)
{
	int result_status;

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
	obj->has_volume = FALSE;
	obj->calc_obj_hit = calc_plane_obj_hit;
	obj->calc_normal = calc_plane_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_plane;
	obj->get_pos = get_plane_pos;
	obj->get_dir = get_plane_dir;
	result_status = set_material(obj, line_element, 3);
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_plane_bump_normal;
	return (result_status);
}

t_binary_result	config_cylinder(char **line_element, t_obj *obj)
{
	int	result_status;

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
	obj->shape.cylinder.radius_pow2 = 0.0f;
	obj->shape.cylinder.p1 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cylinder.p2 = (t_vector){0.0f, 0.0f, 0.0f};
	obj->shape.cylinder.delta_p = (t_vector){0.0f, 0.0f, 0.0f};
	obj->has_volume = TRUE;
	obj->calc_obj_hit = calc_cylinder_obj_hit;
	obj->calc_normal = calc_cylinder_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_cylinder;
	obj->get_pos = get_cylinder_pos;
	obj->get_dir = get_cylinder_dir;
	result_status = set_material(obj, line_element, 5);
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_cylinder_bump_normal;
	return (result_status);
}
