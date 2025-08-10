/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:26:45 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:23:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	parse_cone_config(char **line_element, t_obj *obj)
{
	set_vector(&(obj->shape.cone.pos), line_element[1]);
	set_vector(&(obj->shape.cone.dir), line_element[2]);
	if (is_normal_range(obj->shape.cone.dir) == FALSE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	obj->shape.cone.h = ft_atof(line_element[3]);
	obj->shape.cone.h2 = ft_atof(line_element[4]);
	if (obj->shape.cone.h < 0.0f || obj->shape.cone.h2 < 0.0f)
		return (put_out_format_error(line_element[0], ERR_HEIGHT_ARG));
	obj->shape.cone.angle = ft_atof(line_element[5]);
	if (set_material(obj, line_element + 6, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	set_cone_obj_funcs(t_obj *obj)
{
	obj->calc_obj_hit = calc_cone_obj_hit;
	obj->calc_normal = calc_cone_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_cone;
	obj->get_pos = get_cone_pos;
	obj->get_dir = get_cone_dir;
	obj->reset_obj = reset_object_cone;
	obj->print_rt = print_rt_cone;
	obj->change_size = change_cone_size;
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_cone_bump_normal;
	if (obj->material.is_checkerboard == TRUE)
		obj->get_color = get_cone_checker_color;
	if (obj->material.has_texture == TRUE)
		obj->get_color = get_cone_texture_color;
	obj->set_local_xyz = set_local_xyz_cone;
}

t_binary_result	parse_obj_cone(char **line_element, t_obj *obj, t_bool is_bonus)
{
	if (format_check_cone(line_element, is_bonus) == FAILURE)
		return (FAILURE);
	if (parse_cone_config(line_element, obj) == FAILURE)
		return (FAILURE);
	obj->shape.cone.pos_initial = obj->shape.cone.pos;
	obj->shape.cone.dir_initial = obj->shape.cone.dir;
	obj->shape.cone.h_initial = obj->shape.cone.h;
	obj->shape.cone.h2_initial = obj->shape.cone.h2;
	obj->shape.cone.angle_initial = obj->shape.cone.angle;
	obj->has_volume = FALSE;
	set_cone_obj_funcs(obj);
	return (SUCCESS);
}
