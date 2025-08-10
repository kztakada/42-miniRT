/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:19:29 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 18:35:02 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define DEFAULT_UV_POS 0.5F

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

void	calc_cone_stretch_mapping_uv(t_cone *cone, float axis_projection,
		t_vector local_pos, float *uv)
{
	if (axis_projection > 0.0F)
		calc_stretch_mapping_uv(local_pos, cone->dir, cone->h, uv);
	if (axis_projection < 0.0F)
		calc_stretch_mapping_uv(local_pos, inverse_vector(cone->dir), cone->h2,
			uv);
}
