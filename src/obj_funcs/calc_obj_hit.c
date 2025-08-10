/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:41:03 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:44:34 by katakada         ###   ########.fr       */
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
	solution.discriminant = b * b - 4 * a * c;
	if (solution.discriminant < 0)
		return (solution);
	solution.t1 = (-b - sqrt(solution.discriminant)) / (2.0f * a);
	solution.t2 = (-b + sqrt(solution.discriminant)) / (2.0f * a);
	return (solution);
}

t_hit	calc_sphere_obj_hit(t_obj *obj, t_ray *pov_ray)
{
	t_hit					hit;
	t_quadratic_solution	solution;

	hit = get_zero_hit();
	solution = calc_sphere_quadratic_discriminant(obj, pov_ray);
	if (solution.discriminant < 0)
		return (get_zero_hit());
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
