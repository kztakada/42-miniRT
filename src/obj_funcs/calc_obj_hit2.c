/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:47:51 by katakada          #+#    #+#             */
/*   Updated: 2025/07/29 22:01:15 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 未確認
t_hit	calc_cylinder_obj_hit(t_obj *obj, t_ray *pov_ray)
{
	t_hit					hit;
	t_vector				oc;
	float					a;
	float					b;
	float					c;
	t_quadratic_solution	solution;

	hit = get_zero_hit();
	oc = sub_vectors(pov_ray->pos, obj->shape.cylinder.pos);
	a = vectors_dot(pov_ray->dir, pov_ray->dir) - powf(vectors_dot(pov_ray->dir,
				obj->shape.cylinder.dir), 2.0F);
	b = 2.0f * (vectors_dot(oc, pov_ray->dir) - vectors_dot(pov_ray->dir,
				obj->shape.cylinder.dir) * vectors_dot(oc,
				obj->shape.cylinder.dir));
	c = vectors_dot(oc, oc) - powf(vectors_dot(oc, obj->shape.cylinder.dir),
			2.0F) - obj->shape.cylinder.radius_pow2;
	solution.discriminant = b * b - 4 * a * c;
	if (solution.discriminant < 0)
		return (get_zero_hit());
	solution.t1 = (-b - sqrt(solution.discriminant)) / (2.0f * a);
	solution.t2 = (-b + sqrt(solution.discriminant)) / (2.0f * a);
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

// 未確認
t_hit	calc_cone_obj_hit(t_obj *obj, t_ray *pov_ray)
{
	t_hit					hit;
	t_vector				oc;
	float					a;
	float					b;
	float					c;
	t_quadratic_solution	solution;

	hit = get_zero_hit();
	oc = sub_vectors(pov_ray->pos, obj->shape.cone.pos);
	a = vectors_dot(pov_ray->dir, pov_ray->dir) - powf(vectors_dot(pov_ray->dir,
				obj->shape.cone.dir), 2.0F);
	b = 2.0f * (vectors_dot(oc, pov_ray->dir) - vectors_dot(pov_ray->dir,
				obj->shape.cone.dir) * vectors_dot(oc, obj->shape.cone.dir));
	c = vectors_dot(oc, oc) - powf(vectors_dot(oc, obj->shape.cone.dir), 2.0F)
		- obj->shape.cone.r2;
	solution.discriminant = b * b - 4 * a * c;
	if (solution.discriminant < 0)
		return (get_zero_hit());
	solution.t1 = (-b - sqrt(solution.discriminant)) / (2.0f * a);
	solution.t2 = (-b + sqrt(solution.discriminant)) / (2.0f * a);
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
