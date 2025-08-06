/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:19:29 by katakada          #+#    #+#             */
/*   Updated: 2025/08/06 18:44:20 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define DEFAULT_UV_POS 0.5F

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

static float	calc_circular_orbit_pos(t_vector axis_u_dir,
		t_vector axis_v_dir, t_vector radial)
{
	float		pos;
	float		to_orbit_theta;
	t_vector	radial_dir;
	t_uv		radial_dir_component;

	radial_dir = normalize_vector(radial);
	radial_dir_component.u = vectors_dot(radial_dir, axis_u_dir);
	radial_dir_component.v = vectors_dot(radial_dir, axis_v_dir);
	// 角度計算（0-1の範囲にマッピング）
	to_orbit_theta = atan2f(radial_dir_component.v, radial_dir_component.u);
	pos = (to_orbit_theta + M_PI) / (2.0F * M_PI); // 0.0 - 1.0
	pos = clampf(pos, 0.0F, 1.0F);                 // 範囲外の値をクランプ
	return (pos);
}

void	calc_stretch_mapping_uv(t_vector local_pos, t_vector obj_dir,
		float height, float *uv)
{
	t_vector	radial;
	float		axis_projection;
	t_vector	axis_u_dir;
	t_vector	axis_v_dir;

	// 軸方向の成分を除去して径方向ベクトルを計算
	axis_projection = vectors_dot(local_pos, obj_dir);
	radial = sub_vectors(local_pos, scale_vector(axis_projection, obj_dir));
	uv[0] = DEFAULT_UV_POS; // 任意のU座標
	// 径方向ベクトルが極めて小さい場合（軸上の点）
	if (!(vector_len(radial) < EPSILON))
	{
		if (handle_gimbal_lock_uv_axes(obj_dir, &axis_u_dir, &axis_v_dir))
			uv[0] = calc_circular_orbit_pos(axis_u_dir, axis_v_dir, radial);
	}
	// ストレッチマッピングを適用
	uv[1] = clampf((axis_projection / height), 0.0F, 1.0F); // V座標にストレッチ適用
}
