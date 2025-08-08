/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:27:28 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 23:45:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	parse_plane_config(char **line_element, t_obj *obj)
{
	set_vector(&(obj->shape.plane.pos), line_element[1]);
	set_vector(&(obj->shape.plane.dir), line_element[2]);
	if (is_normal_range(obj->shape.plane.dir) == FALSE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	if (set_material(obj, line_element + 3, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	set_plane_obj_funcs(t_obj *obj)
{
	obj->calc_obj_hit = calc_plane_obj_hit;
	obj->calc_normal = calc_plane_normal;
	obj->get_color = get_color;
	obj->print_focused_obj = print_focused_obj_plane;
	obj->get_pos = get_plane_pos;
	obj->get_dir = get_plane_dir;
	obj->reset_obj = reset_object_plane;
	obj->print_rt = print_rt_plane;
	if (obj->material.has_bump == TRUE)
		obj->calc_normal = calc_plane_bump_normal;
	if (obj->material.is_checkerboard == TRUE)
		obj->get_color = get_plane_checker_color;
	if (obj->material.has_texture == TRUE)
		obj->get_color = get_plane_texture_color;
	obj->set_local_xyz = set_local_xyz_plane;
}

t_binary_result	parse_obj_plane(char **line_element, t_obj *obj,
		t_bool is_bonus)
{
	if (format_check_plane(line_element, is_bonus) == FAILURE)
		return (FAILURE);
	if (parse_plane_config(line_element, obj) == FAILURE)
		return (FAILURE);
	obj->shape.plane.pos_initial = obj->shape.plane.pos;
	obj->shape.plane.dir_initial = obj->shape.plane.dir;
	obj->has_volume = FALSE;
	set_plane_obj_funcs(obj);
	return (SUCCESS);
}
