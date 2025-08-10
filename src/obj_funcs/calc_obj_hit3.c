/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:56:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/10 19:57:13 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define  NO_SOLUTION -1.0f

static float	calc_cylinder_t(t_ray *ray, t_cylinder *cyl, t_vector oc)
{
	float	abc[3];
	float	d_z;
	float	o_z;
	float	t;

	d_z = vectors_dot(ray->dir, cyl->dir);
	o_z = vectors_dot(oc, cyl->dir);
	abc[0] = vectors_dot(ray->dir, ray->dir) - d_z * d_z;
	abc[1] = 2.0f * (vectors_dot(ray->dir, oc) - d_z * o_z);
	abc[2] = vectors_dot(oc, oc) - cyl->radius_pow2 - o_z * o_z;
	t = solve_quadratic(abc[0], abc[1], abc[2]);
	if (t < 0)
		return (NO_SOLUTION);
	oc = get_ray_pos_at_t(*ray, t);
	o_z = vectors_dot(sub_vectors(oc, cyl->pos), cyl->dir);
	if (o_z < 0 || o_z > cyl->height)
	{
		t = (-abc[1] + sqrtf(abc[1] * abc[1] - 4 * abc[0] * abc[2]))
			/ (2 * abc[0]);
		oc = get_ray_pos_at_t(*ray, t);
		o_z = vectors_dot(sub_vectors(oc, cyl->pos), cyl->dir);
		if (t < EPSILON || o_z < 0 || o_z > cyl->height)
			return (NO_SOLUTION);
	}
	return (t);
}

/* 円筒側面との交差判定 */
static t_hit	calc_cylinder_side_hit(t_ray *ray, t_cylinder *cyl)
{
	t_vector	oc;
	float		t;

	oc = sub_vectors(ray->pos, cyl->pos);
	t = calc_cylinder_t(ray, cyl, oc);
	if (t < 0)
		return (get_zero_hit());
	return (set_hit_info(t, ray));
}

/* 円筒全体との交差判定 */
t_hit	calc_cylinder_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cylinder	*cyl;
	t_hit		hits[3];

	cyl = &obj->shape.cylinder;
	hits[0] = calc_cylinder_side_hit(ray, cyl);
	hits[1] = calc_disk_obj_hit(cyl->pos, scale_vector(-1.0f, cyl->dir),
			cyl->radius_pow2, ray);
	hits[2] = calc_disk_obj_hit(add_vectors(cyl->pos, scale_vector(cyl->height,
					cyl->dir)), cyl->dir, cyl->radius_pow2, ray);
	return (get_nearest_hit(hits, 3));
}