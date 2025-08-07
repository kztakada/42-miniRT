/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:27:34 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 21:12:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 未実装
t_vector	calc_cylinder_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;
	t_cylinder	*cyl;
	t_vector	axis;
	t_vector	center_to_hit;
	float		dist_along_axis;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	cyl = &obj->shape.cylinder;
	axis = normalize_vector(cyl->dir);
	// 円柱の中心軸から交点へのベクトルを計算
	center_to_hit = sub_vectors(hit->pos, cyl->pos);
	// 中心軸に沿った距離を計算
	dist_along_axis = vectors_dot(center_to_hit, axis);
	// 底面との交点の場合
	if (fabsf(dist_along_axis) < EPSILON)
		return (scale_vector(-1.0f, axis));
	// 上面との交点の場合
	if (fabsf(dist_along_axis - cyl->height) < EPSILON)
		return (axis);
	// 側面との交点の場合：中心軸に投影した点から交点へのベクトル
	normal = sub_vectors(center_to_hit, scale_vector(dist_along_axis, axis));
	return (normalize_vector(normal));
}

t_vector	calc_cone_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;
	t_cone		*cone;
	t_vector	axis;
	t_vector	center_to_hit;
	float		dist_along_axis;
	float		cos_angle;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	cone = &obj->shape.cone;
	axis = normalize_vector(cone->dir);
	// 円錐の先端から交点へのベクトルを計算
	center_to_hit = sub_vectors(hit->pos, cone->pos);
	// 中心軸に沿った距離を計算
	dist_along_axis = vectors_dot(center_to_hit, axis);
	// 底面との交点の場合（高さhでの平面）
	if (fabsf(dist_along_axis - cone->h) < EPSILON)
	{
		// 底面の法線は常に軸方向だが、視線の向きに応じて反転させる
		if (vectors_dot(axis, hit->pov_dir) > 0)
			return (scale_vector(-1.0f, axis));
		return (axis);
	}
	// 円錐の先端での交点の場合（ただし、これは通常発生しにくい）
	if (fabsf(dist_along_axis) < EPSILON && vector_len(center_to_hit) < EPSILON)
		return (scale_vector(-1.0f, axis));
	// 側面との交点の場合
	cos_angle = cosf(cone->angle);
	// 中心軸に投影した点から交点へのベクトル（放射方向）
	normal = sub_vectors(center_to_hit, scale_vector(dist_along_axis, axis));
	// 円錐の側面の法線は、軸と放射方向の両方の成分を持つ
	normal = add_vectors(normal, scale_vector(cos_angle * cos_angle, axis));
	// 法線が常に外側を向くようにする
	if (vectors_dot(normal, hit->pov_dir) > 0)
		normal = scale_vector(-1.0f, normal);
	return (normalize_vector(normal));
}
