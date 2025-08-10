/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:26:57 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:26:47 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	parse_cylinder_config(char **line_element, t_obj *obj)
{
	set_vector(&(obj->shape.cylinder.pos), line_element[1]);
	set_vector(&(obj->shape.cylinder.dir), line_element[2]);
	if (is_normal_range(obj->shape.cylinder.dir) == FALSE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	obj->shape.cylinder.diameter = ft_atof(line_element[3]);
	if (obj->shape.cylinder.diameter < 0.0f)
		return (put_out_format_error(line_element[0], ERR_DIAMETER_ARG));
	obj->shape.cylinder.height = ft_atof(line_element[4]);
	if (obj->shape.cylinder.height < 0.0f)
		return (put_out_format_error(line_element[0], ERR_HEIGHT_ARG));
	if (set_material(obj, line_element + 5, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	set_cylinder_obj_funcs(t_obj *obj)
{
	obj->calc_obj_hit = calc_cylinder_obj_hit;
	obj->calc_normal = calc_cylinder_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_cylinder;
	obj->get_pos = get_cylinder_pos;
	obj->get_dir = get_cylinder_dir;
	obj->reset_obj = reset_object_cylinder;
	obj->print_rt = print_rt_cylinder;
	obj->change_size = change_cylinder_size;
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_cylinder_bump_normal;
	if (obj->material.is_checkerboard == TRUE)
		obj->get_color = get_cylinder_checker_color;
	if (obj->material.has_texture == TRUE)
		obj->get_color = get_cylinder_texture_color;
	obj->set_local_xyz = set_local_xyz_cylinder;
}

t_binary_result	parse_obj_cylinder(char **line_element, t_obj *obj,
		t_bool is_bonus)
{
	if (format_check_cylinder(line_element, is_bonus) == FAILURE)
		return (FAILURE);
	if (parse_cylinder_config(line_element, obj) == FAILURE)
		return (FAILURE);
	obj->shape.cylinder.pos_initial = obj->shape.cylinder.pos;
	obj->shape.cylinder.dir_initial = obj->shape.cylinder.dir;
	obj->shape.cylinder.diameter_initial = obj->shape.cylinder.diameter;
	obj->shape.cylinder.height_initial = obj->shape.cylinder.height;
	obj->shape.cylinder.radius_pow2 = obj->shape.cylinder.diameter
		* obj->shape.cylinder.diameter * 0.25f;
	obj->has_volume = TRUE;
	set_cylinder_obj_funcs(obj);
	return (SUCCESS);
}
