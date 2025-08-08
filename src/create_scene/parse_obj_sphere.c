/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:27:14 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 23:45:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	parse_sphere_config(char **line_element, t_obj *obj)
{
	set_vector(&(obj->shape.sphere.pos), line_element[1]);
	obj->shape.sphere.diameter = ft_atof(line_element[2]);
	if (obj->shape.sphere.diameter < 0.0f)
		return (put_out_format_error(line_element[0], ERR_DIAMETER_ARG));
	if (set_material(obj, line_element + 3, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	set_sphere_obj_funcs(t_obj *obj)
{
	obj->calc_obj_hit = calc_sphere_obj_hit;
	obj->calc_normal = calc_sphere_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_sphere;
	obj->get_pos = get_sphere_pos;
	obj->get_dir = get_sphere_dir;
	obj->reset_obj = reset_object_sphere;
	obj->print_rt = print_rt_sphere;
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_sphere_bump_normal;
	if (obj->material.is_checkerboard == TRUE)
		obj->get_color = get_sphere_checker_color;
	if (obj->material.has_texture == TRUE)
		obj->get_color = get_sphere_texture_color;
	obj->set_local_xyz = set_local_xyz_sphere;
}

t_binary_result	parse_obj_sphere(char **line_element, t_obj *obj,
		t_bool is_bonus)
{
	if (format_check_sphere(line_element, is_bonus) == FAILURE)
		return (FAILURE);
	if (parse_sphere_config(line_element, obj) == FAILURE)
		return (FAILURE);
	obj->shape.sphere.pos_initial = obj->shape.sphere.pos;
	obj->shape.sphere.radius_pow2 = obj->shape.sphere.diameter
		* obj->shape.sphere.diameter * 0.25f;
	obj->shape.sphere.rotation_y = 0.0f;
	obj->has_volume = TRUE;
	set_sphere_obj_funcs(obj);
	return (SUCCESS);
}
