/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:47:51 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 19:53:55 by kharuya          ###   ########.fr       */
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

static float	calc_cone_t(t_vector ray_dir, t_vector cone_dir,
	t_vector oc, float tan2_alpha)
{
	float	a;
	float	b;
	float	c;
	float	d_z;
	float	o_z;

	d_z = vectors_dot(ray_dir, cone_dir);
	o_z = vectors_dot(oc, cone_dir);
	a = vectors_dot(ray_dir, ray_dir) - (1.0f + tan2_alpha) * d_z * d_z;
	b = 2.0f * (vectors_dot(ray_dir, oc) - (1.0f + tan2_alpha) * d_z * o_z);
	c = vectors_dot(oc, oc) - (1.0f + tan2_alpha) * o_z * o_z;
	return (solve_quadratic(a, b, c));
}

/* 円錐側面との交差判定 */
static t_hit	calc_cone_side_hit(t_ray *ray, t_cone *cone)
{
	float		t;
	float		tan2_alpha;
	float		m;
	t_vector	hit_point;
	t_vector	oc;

	oc = sub_vectors(ray->pos, cone->pos);
	tan2_alpha = tanf(cone->angle) * tanf(cone->angle);
	t = calc_cone_t(ray->dir, cone->dir, oc, tan2_alpha);
	if (t < EPSILON)
		return (get_zero_hit());
	hit_point = get_ray_pos_at_t(*ray, t);
	m = vectors_dot(sub_vectors(hit_point, cone->pos), cone->dir);
	if (m < -cone->h2 || m > cone->h)
		return (get_zero_hit());
	return (set_hit_info(t, ray));
}

/* 円錐全体との交差判定 */
t_hit	calc_cone_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cone		*cone;
	t_hit		hits[3];
	t_vector	disk_center;
	float		disk_radius2;
	t_vector	disk_normal;

	if (!obj || !ray)
		return (get_zero_hit());
	cone = &obj->shape.cone;
	hits[0] = calc_cone_side_hit(ray, cone);
	disk_center = add_vectors(cone->pos, scale_vector(cone->h, cone->dir));
	disk_radius2 = powf(cone->h * tanf(cone->angle), 2);
	disk_normal = cone->dir;
	hits[1] = calc_disk_obj_hit(disk_center, disk_normal, disk_radius2, ray);
	disk_center = add_vectors(cone->pos, scale_vector(cone->h2,
				inverse_vector(cone->dir)));
	disk_radius2 = powf(cone->h2 * tanf(cone->angle), 2);
	disk_normal = inverse_vector(cone->dir);
	hits[2] = calc_disk_obj_hit(disk_center, disk_normal, disk_radius2, ray);
	return (get_nearest_hit(hits, 3));
}
