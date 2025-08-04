/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:47:51 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 23:35:05 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 二次方程式を解いて、最も近い正の解を返す */
static float	solve_quadratic(float a, float b, float c)
{
	float	discr;
	float	t1;
	float	t2;
	float	t;

	discr = b * b - 4.0f * a * c;
	if (discr < 0 || fabs(a) < EPSILON)
		return (-1.0f);
	t1 = (-b - sqrtf(discr)) / (2.0f * a);
	t2 = (-b + sqrtf(discr)) / (2.0f * a);
	if (t1 > EPSILON)
		t = t1;
	else
		t = t2;
	if (t < EPSILON)
	{
		if (t2 > EPSILON)
			t = t2;
		else
			t = t1;
	}
	if (t < EPSILON)
		return (-1.0f);
	return (t);
}

/* 交点情報を設定 */
static void	set_hit_info(t_hit *hit, float t, t_ray *ray, t_vector normal)
{
	hit->is_hit = TRUE;
	hit->t = t;
	hit->pos = get_ray_pos_at_t(*ray, t);
	hit->pov_dir = ray->dir;
	hit->normal = normal;
	if (vectors_dot(hit->normal, ray->dir) > 0)
		hit->normal = scale_vector(-1.0f, hit->normal);
}

/* 円盤との交差判定 */
static t_hit	calc_disk_obj_hit(t_vector center, t_vector normal, float radius2, t_ray *ray)
{
	t_hit		hit;
	float		denom;
	float		t;
	t_vector	hit_point;

	hit = get_zero_hit();
	denom = vectors_dot(ray->dir, normal);
	if (fabs(denom) < EPSILON)
		return (hit);
	t = vectors_dot(sub_vectors(center, ray->pos), normal) / denom;
	if (t < EPSILON)
		return (hit);
	hit_point = get_ray_pos_at_t(*ray, t);
	if (vectors_dot(sub_vectors(hit_point, center), sub_vectors(hit_point, center)) > radius2)
		return (hit);
	set_hit_info(&hit, t, ray, normal);
	return (hit);
}

/* 円筒側面との交差判定 */
static t_hit	calc_cylinder_side_hit(t_ray *ray, t_vector pos, t_vector dir, 
				float radius2, float height)
{
	t_hit		hit;
	t_vector	oc;
	float		d[2];
	float		q[3];
	float		t;

	hit = get_zero_hit();
	oc = sub_vectors(ray->pos, pos);
	d[0] = vectors_dot(ray->dir, dir);
	d[1] = vectors_dot(oc, dir);
	q[0] = vectors_dot(ray->dir, ray->dir) - d[0] * d[0];
	q[1] = 2.0f * (vectors_dot(ray->dir, oc) - d[0] * d[1]);
	q[2] = vectors_dot(oc, oc) - d[1] * d[1] - radius2;
	if ((t = solve_quadratic(q[0], q[1], q[2])) < 0)
		return (hit);
	oc = get_ray_pos_at_t(*ray, t);
	if ((d[1] = vectors_dot(sub_vectors(oc, pos), dir)) < 0 || d[1] > height)
	{
		t = (-q[1] + sqrtf(q[1] * q[1] - 4 * q[0] * q[2])) / (2 * q[0]);
		if (t < EPSILON || (d[1] = vectors_dot(sub_vectors(
			(oc = get_ray_pos_at_t(*ray, t)), pos), dir)) < 0 || d[1] > height)
			return (hit);
	}
	set_hit_info(&hit, t, ray, normalize_vector(sub_vectors(oc, 
		add_vectors(pos, scale_vector(d[1], dir)))));
	return (hit);
}

/* 円筒全体との交差判定 */
t_hit	calc_cylinder_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cylinder	*cyl;
	t_vector	dir;
	t_hit		hits[3];
	t_hit		nearest;
	int			i;

	cyl = &obj->shape.cylinder;
	dir = normalize_vector(cyl->dir);
	hits[0] = calc_cylinder_side_hit(ray, cyl->pos, dir, cyl->radius_pow2, cyl->height);
	hits[1] = calc_disk_obj_hit(cyl->pos, scale_vector(-1.0f, dir), cyl->radius_pow2, ray);
	hits[2] = calc_disk_obj_hit(add_vectors(cyl->pos, scale_vector(cyl->height, dir)), 
		dir, cyl->radius_pow2, ray);
	nearest = get_zero_hit();
	i = 0;
	while (i < 3)
	{
		if (hits[i].is_hit && (!nearest.is_hit || hits[i].t < nearest.t))
			nearest = hits[i];
		i++;
	}
	return (nearest);
}

/* 円錐側面との交差判定 */
static t_hit	calc_cone_side_hit(t_obj *obj, t_ray *ray)
{
	t_hit		hit;
	t_cone		*cone;
	t_vector	oc;
	float		a, b, c;
	float		t;
	float		m;
	t_vector	p;
	t_vector	normal;

	hit = get_zero_hit();
	cone = &obj->shape.cone;
	oc = sub_vectors(ray->pos, cone->pos);

	// 円錐の方向ベクトルを正規化
	t_vector dir = normalize_vector(cone->dir);

	// cos²(θ)の値を取得（θは円錐の開き角）
	float cos2 = cone->cos2;

	// 二次方程式の係数を計算
	float dot_v_d = vectors_dot(ray->dir, dir);
	float dot_oc_d = vectors_dot(oc, dir);

	a = dot_v_d * dot_v_d - cos2 * vectors_dot(ray->dir, ray->dir);
	b = 2.0f * (dot_v_d * dot_oc_d - cos2 * vectors_dot(ray->dir, oc));
	c = dot_oc_d * dot_oc_d - cos2 * vectors_dot(oc, oc);

	// 二次方程式を解く
	t = solve_quadratic(a, b, c);
	if (t < EPSILON)
		return (hit);

	// 交点が円錐の高さ内にあるか確認
	p = get_ray_pos_at_t(*ray, t);
	m = vectors_dot(sub_vectors(p, cone->pos), dir);
	if (m < 0 || m > cone->h)
		return (hit);

	// 法線ベクトルを計算
	normal = sub_vectors(sub_vectors(p, cone->pos),
			scale_vector((1 + cos2) * m / cos2, dir));
	normal = normalize_vector(normal);

	// 交点情報を設定
	set_hit_info(&hit, t, ray, normal);
	return (hit);
}

/* 円錐全体との交差判定 */
t_hit	calc_cone_obj_hit(t_obj *obj, t_ray *ray)
{
	t_cone		*cone;
	t_vector	dir;
	t_hit		hits[2];
	t_hit		nearest;
	int			i;

	cone = &obj->shape.cone;
	dir = normalize_vector(cone->dir);

	// 円錐側面との交差判定
	hits[0] = calc_cone_side_hit(obj, ray);

	// 円錐底面（大きい方の円）との交差判定
	hits[1] = calc_disk_obj_hit(
		add_vectors(cone->pos, scale_vector(cone->h, dir)),
		dir,
		cone->h * cone->h * tanf(cone->angle) * tanf(cone->angle),
		ray);

	// 最も近い交点を見つける
	nearest = get_zero_hit();
	i = 0;
	while (i < 2)
	{
		if (hits[i].is_hit && (!nearest.is_hit || hits[i].t < nearest.t))
			nearest = hits[i];
		i++;
	}
	return (nearest);
}
