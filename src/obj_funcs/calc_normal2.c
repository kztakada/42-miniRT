/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:27:34 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 10:48:50 by kharuya          ###   ########.fr       */
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
	t_vector	hit_to_tip;
	t_vector	proj_point;
	float		scalar;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	cone = &obj->shape.cone;
	hit_to_tip = sub_vectors(hit->pos, cone->pos);
	// 底面との交点の場合
	if (vectors_dot(hit_to_tip, cone->dir) > cone->h - EPSILON)
		return (inverse_vector(cone->dir));
	scalar = vectors_dot(hit_to_tip, cone->dir);
	proj_point = add_vectors(cone->pos, scale_vector(scalar, cone->dir));
	normal = sub_vectors(hit->pos, proj_point);
	return (normalize_vector(normal));
}
