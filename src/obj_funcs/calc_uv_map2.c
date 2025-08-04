/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:19:29 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 22:11:39 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	calc_cylinder_side_uv(t_vector local_pos, t_vector axis, float height,
		float *uv)
{
	t_vector	radial_vec;
	float		axis_projection;
	float		angle;

	// 軸方向の成分を除去して径方向ベクトルを計算
	axis_projection = vectors_dot(local_pos, axis);
	radial_vec = sub_vectors(local_pos, scale_vector(axis_projection, axis));
	radial_vec = normalize_vector(radial_vec);
	// 角度計算（0-1の範囲にマッピング）
	angle = atan2(radial_vec.z, radial_vec.x);
	if (angle < 0)
		angle += 2.0f * M_PI;
	uv[0] = angle / (2.0f * M_PI);
	// 高さ方向（-height/2 から height/2 を 0-1 にマッピング）
	uv[1] = (axis_projection + height / 2.0f) / height;
	// 境界クランプ
	uv[0] = fmaxf(0.0f, fminf(1.0f, uv[0]));
	uv[1] = fmaxf(0.0f, fminf(1.0f, uv[1]));
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
