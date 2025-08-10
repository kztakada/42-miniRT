/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:41:03 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 05:30:03 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_quadratic_solution	calc_sphere_quadratic_discriminant(t_obj *obj,
		t_ray *pov_ray)
{
	t_vector				oc;
	float					a;
	float					b;
	float					c;
	t_quadratic_solution	solution;

	oc = sub_vectors(pov_ray->pos, obj->shape.sphere.pos);
	a = vectors_dot(pov_ray->dir, pov_ray->dir);
	b = 2.0f * vectors_dot(oc, pov_ray->dir);
	c = vectors_dot(oc, oc) - obj->shape.sphere.radius_pow2;
	// 判別式
	solution.discriminant = b * b - 4 * a * c;
	// 判別式が負の場合、解なし
	if (solution.discriminant < 0)
		return (solution);
	// 2つの解を計算
	solution.t1 = (-b - sqrt(solution.discriminant)) / (2.0f * a);
	solution.t2 = (-b + sqrt(solution.discriminant)) / (2.0f * a);
	return (solution);
}

t_hit	calc_sphere_obj_hit(t_obj *obj, t_ray *pov_ray)
{
	t_hit					hit;
	t_quadratic_solution	solution;

	hit = get_zero_hit();
	// 二次方程式の係数を計算
	solution = calc_sphere_quadratic_discriminant(obj, pov_ray);
	if (solution.discriminant < 0)
		return (get_zero_hit());
	// 最小の正の値を選択
	if (solution.t1 > EPSILON)
		hit.t = solution.t1;
	else if (solution.t2 > EPSILON)
		hit.t = solution.t2;
	else
		return (get_zero_hit());
	hit.is_hit = TRUE;
	hit.pos = get_ray_pos_at_t(*pov_ray, hit.t);
	return (hit);
}

// t_hit	calc_sphere_obj_hit(t_obj *obj, t_ray *pov_ray)
// {
// 	t_hit		hit;
// 	t_vector	to_pov_ray;
// 	float		nearest_t;
// 	float		gap_t;
// 	float		dist_pow2_to_nearest;

// 	hit = get_zero_hit();
// 	to_pov_ray = sub_vectors(pov_ray->pos, obj->shape.sphere.pos);
// 	nearest_t = vectors_dot(to_pov_ray, pov_ray->dir);
// 	if (nearest_t < 0)
// 		return (get_zero_hit());
// 	dist_pow2_to_nearest = vectors_dot(to_pov_ray, to_pov_ray) - powf(nearest_t,
// 			2.0F);
// 	if (dist_pow2_to_nearest > obj->shape.sphere.radius_pow2)
// 		return (get_zero_hit());
// 	gap_t = sqrt(obj->shape.sphere.radius_pow2 - dist_pow2_to_nearest);
// 	hit.t = nearest_t - gap_t;
// 	if (hit.t < EPSILON)
// 		hit.t = nearest_t + gap_t;
// 	if (hit.t < EPSILON)
// 		return (get_zero_hit());
// 	hit.is_hit = TRUE;
// 	hit.pos = get_ray_pos_at_t(*pov_ray, hit.t);
// 	printf("Sphere is hit: %d, pos: (%f, %f, %f)\n", hit.is_hit, hit.pos.x,
// 		hit.pos.y, hit.pos.z);
// 	printf("Sphere color: (%f, %f, %f)\n", obj->material.color.r,
// 		obj->material.color.g, obj->material.color.b);
// 	return (hit);
// }

t_hit	calc_plane_obj_hit(t_obj *obj, t_ray *pov_ray)
{
	t_hit		hit;
	float		denominator;
	float		t;
	t_vector	plane_pos;
	t_vector	plane_normal;

	hit = get_zero_hit();
	plane_pos = obj->shape.plane.pos;
	plane_normal = obj->shape.plane.dir;
	denominator = vectors_dot(pov_ray->dir, plane_normal);
	if (fabs(denominator) < EPSILON)
		return (hit);
	t = vectors_dot(sub_vectors(plane_pos, pov_ray->pos), plane_normal)
		/ denominator;
	if (t < EPSILON)
		return (get_zero_hit());
	hit.is_hit = TRUE;
	hit.t = t;
	hit.pos = get_ray_pos_at_t(*pov_ray, hit.t);
	if (denominator > 0)
		hit.normal = scale_vector(-1.0f, plane_normal);
	else
		hit.normal = plane_normal;
	return (hit);
}
