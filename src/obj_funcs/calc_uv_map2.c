/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:19:29 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 18:19:55 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_plane_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	relative_pos;

	if (!obj || !uv_map)
		return ;
	relative_pos = sub_vectors(target_pos, obj->shape.plane.pos);
	uv_map[0] = vectors_dot(relative_pos, obj->local.x);
	uv_map[1] = vectors_dot(relative_pos, obj->local.z);
}

static void	calc_solid_of_revolution_uv_map_xy(t_local_axes obj_local,
		t_vector to_target, float *uv_map, float obj_height)
{
	t_vector	target_dir;
	t_vector	local_pos;

	if (!uv_map)
		return ;
	local_pos.y = vectors_dot(obj_local.y, to_target);
	target_dir = normalize_vector(to_target);
	local_pos.x = vectors_dot(obj_local.x, target_dir);
	local_pos.z = vectors_dot(obj_local.z, target_dir);
	uv_map[0] = atan2f(target_dir.x, target_dir.z) / (2.0F * (float)M_PI)
		+ 0.5F;
	uv_map[1] = local_pos.y / obj_height + 0.5F;
}

void	calc_cylinder_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	to_target;

	if (!obj || !uv_map)
		return ;
	to_target = sub_vectors(obj->shape.cylinder.pos, target_pos);
	calc_solid_of_revolution_uv_map_xy(obj->local, to_target, uv_map,
		obj->shape.cylinder.height);
}

void	calc_cone_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	to_target;

	if (!obj || !uv_map)
		return ;
	to_target = sub_vectors(obj->shape.cone.pos, target_pos);
	calc_solid_of_revolution_uv_map_xy(obj->local, to_target, uv_map,
		obj->shape.cone.h + obj->shape.cone.h2);
}
