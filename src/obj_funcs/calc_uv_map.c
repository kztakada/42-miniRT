/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:26:56 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 18:52:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_sphere_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	target_dir;
	t_vector	local_pos;

	if (!obj || !uv_map)
		return ;
	target_dir = normalize_vector(sub_vectors(obj->shape.sphere.pos,
				target_pos));
	local_pos.x = vectors_dot(target_dir, obj->local.x);
	local_pos.y = vectors_dot(target_dir, obj->local.y);
	local_pos.z = vectors_dot(target_dir, obj->local.z);
	uv_map[0] = atan2f(local_pos.z, local_pos.x) / (2.0F * (float)M_PI) + 0.5F;
	uv_map[1] = local_pos.y * 0.5F + 0.5F;
}

void	calc_sphere_uv_map_equirectangular(t_obj *obj, t_vector hit_pos,
		float *uv, float rotation_y)
{
	t_vector	local_point;

	float phi;   // 方位角（経度）
	float theta; // 仰角（緯度の補角）
	if (!obj || !uv)
		return ;
	if (obj->shape.sphere.diameter / 2.0F < EPSILON)
	{
		uv[0] = 0.5F;
		uv[1] = 0.5F;
		return ;
	}
	// 球面座標系に変換
	local_point = normalize_vector(sub_vectors(hit_pos, obj->shape.sphere.pos));
	// 仰角（theta）: 0（北極）から π（南極）
	theta = acosf(clampf(local_point.y, -1.0f, 1.0f)); // 0.0 ～ 1.0
	// 方位角（phi）: -π から π
	phi = atan2f(local_point.z, local_point.x); // 0.0 ～ 1.0
	// 回転を適用
	phi += rotation_y * (float)M_PI;
	// UV座標に変換
	uv[0] = (phi + M_PI) / (2.0f * M_PI);
	uv[1] = theta / M_PI; // 0.0 ～ 1.0
	//　マイナス値、範囲外の値の修正
	uv[0] = fmod(uv[0], 1.0f);
	if (uv[0] < 0.0f)
		uv[0] += 1.0f;
	// 反転の修正（地球テクスチャ用）
	uv[0] = 1.0f - uv[0]; // 水平反転
	// uv[1] = 1.0f - uv[1];  // 垂直反転（必要に応じてコメントアウト）
	// UV座標のクランプ
	uv[0] = clampf(uv[0], 0.0f, 1.0f);
	uv[1] = clampf(uv[1], 0.0f, 1.0f);
}
