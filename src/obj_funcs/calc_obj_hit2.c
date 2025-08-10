/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:47:51 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 19:57:36 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
