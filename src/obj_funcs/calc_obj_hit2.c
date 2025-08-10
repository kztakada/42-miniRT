/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:47:51 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 19:38:59 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	calc_cylinder_t(t_vector ray_dir, t_vector cylinder_dir, t_vector oc)
{
	float	a;
	float	b;
	float	c;
	float	d_z;  // レイの方向と円錐軸の内積
	float	o_z;   // OCベクトルと円錐軸の内積

	d_z = vectors_dot(ray_dir, cylinder_dir);
	o_z = vectors_dot(oc, cylinder_dir);
	a = vectors_dot(ray_dir, ray_dr) - d_z * d_z;
	b = 2.0f * (vectors_dot(ray_dir, oc) - d_z * oc_dot_cyl_axis);
	c = vectors_dot(oc, oc) - d_z * d_z - radius2;
	return (solve_quadratic(a, b, c));
}

/* 円筒側面との交差判定 */
static t_hit	calc_cylinder_side_hit(t_ray *ray, t_vector cylinder_pos, t_vector cylinder_dir,
		float radius2, float height)
{
	t_vector	oc;
	float		o_z;
	float		t;

	oc = sub_vectors(ray->pos, cylinder_pos);
	t = calc_cylinder_t(ray->dir, cylinder_dir, oc);
	if (t < 0)
		return (get_zero_hit());
	oc = get_ray_pos_at_t(*ray, t);
	o_z = vectors_dot(sub_vectors(oc, cylinder_pos), cylinder_dir);
	if (o_z < 0 || o_z > height)
	{
		t = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
		oc = get_ray_pos_at_t(*ray, t);
		o_z = vectors_dot(sub_vectors(oc, cylinder_pos), cylinder_dir);
		if (t < EPSILON || o_z < 0 || o_z > height)
			return (get_zero_hit());
	}
	return (set_hit_info(t, ray));
}

/* 円筒全体との交差判定 */
t_hit	calc_cylinder_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cylinder	*cyl;
	t_vector	dir;
	t_hit		hits[3];

	cyl = &obj->shape.cylinder;
	dir = normalize_vector(cyl->dir);
	hits[0] = calc_cylinder_side_hit(ray, cyl->pos, dir, cyl->radius_pow2,
			cyl->height);
	hits[1] = calc_disk_obj_hit(cyl->pos, scale_vector(-1.0f, dir),
			cyl->radius_pow2, ray);
	hits[2] = calc_disk_obj_hit(add_vectors(cyl->pos, scale_vector(cyl->height,
					dir)), dir, cyl->radius_pow2, ray);
	return (get_nearest_hit(hits, 3));
}

static float	calc_cone_t(t_vector ray_dir, t_vector cone_dir, t_vector oc, float tan2_alpha)
{
	float	a;
	float	b;
	float	c;
	float	d_z;  // レイの方向と円錐軸の内積
	float	o_z;   // OCベクトルと円錐軸の内積

	d_z = vectors_dot(ray_dir, cone_dir);
	o_z = vectors_dot(oc, cone_dir);
	a = vectors_dot(ray_dir, ray_dir) - (1.0f + tan2_alpha) * d_z * d_z;
	b = 2.0f * (vectors_dot(ray_dir, oc) - (1.0f + tan2_alpha) * d_z * o_z);
	c = vectors_dot(oc, oc) - (1.0f + tan2_alpha) * o_z * o_z;
	return (solve_quadratic(a, b, c));
}

/* 円錐側面との交差判定 */
static t_hit	calc_cone_side_hit(t_ray *ray, t_vector pos, t_vector cone_dir,
		float angle, float height)
{
	float		t;
	float		tan2_alpha;
	float		m;
	t_vector	hit_point;
	t_vector	oc;

	oc = sub_vectors(ray->pos, pos);
	tan2_alpha = tanf(angle) * tanf(angle);
	t = calc_cone_t(ray->dir, cone_dir, oc, tan2_alpha);
	if (t < EPSILON)
		return (get_zero_hit());
	hit_point = get_ray_pos_at_t(*ray, t);
	m = vectors_dot(sub_vectors(hit_point, pos), cone_dir);
	if (m < 0 || m > height)
		return (get_zero_hit());
	return (set_hit_info(t, ray));
}

/* 円錐全体との交差判定 */
t_hit	calc_cone_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cone		*cone;
	t_hit		hits[2];
	t_vector	disk_center;
	float		disk_radius2;
	t_vector	disk_normal;

	if (!obj || !ray)
		return (get_zero_hit());
	cone = &obj->shape.cone;
	hits[0] = calc_cone_side_hit(ray, cone->pos, cone->dir, cone->angle, cone->h);
	disk_center = add_vectors(cone->pos, scale_vector(cone->h, cone->dir));
	disk_radius2 = powf(cone->h * tanf(cone->angle), 2);
	disk_normal = scale_vector(-1.0f, cone->dir);
	hits[1] = calc_disk_obj_hit(disk_center, disk_normal, disk_radius2, ray);
	return (get_nearest_hit(hits, 2));
}
