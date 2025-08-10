/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj_hit_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:28:07 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/09 10:59:55 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	get_zero_hit(void)
{
	t_hit	hit;

	hit.is_hit = FALSE;
	hit.normal = (t_vector){0.0F, 0.0F, 0.0F};
	hit.pos = (t_vector){0.0F, 0.0F, 0.0F};
	hit.t = -1.0F;
	hit.color = (t_color){0.0F, 0.0F, 0.0F};
	hit.pov_dir = (t_vector){0.0F, 0.0F, 0.0F};
	return (hit);
}

/* 交点情報を設定 */
t_hit	set_hit_info(float t, t_ray *ray)
{
	t_hit	hit;

	hit.is_hit = TRUE;
	hit.t = t;
	hit.pos = get_ray_pos_at_t(*ray, t);
	return (hit);
}

/* 複数の交点から最も近い交点を選択する */
t_hit	get_nearest_hit(t_hit *hits, int hit_count)
{
	t_hit	nearest;
	int		i;

	nearest = get_zero_hit();
	i = 0;
	while (i < hit_count)
	{
		if (hits[i].is_hit && (!nearest.is_hit || hits[i].t < nearest.t))
			nearest = hits[i];
		i++;
	}
	return (nearest);
}

/* 二次方程式を解いて、最も近い正の解を返す */
float	solve_quadratic(float a, float b, float c)
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

/* 円盤との交差判定 */
t_hit	calc_disk_obj_hit(t_vector center, t_vector normal,
		float radius2, t_ray *ray)
{
	float		denom;
	float		t;
	t_vector	hit_point;

	denom = vectors_dot(ray->dir, normal);
	if (fabsf(denom) < EPSILON)
		return (get_zero_hit());
	t = vectors_dot(sub_vectors(center, ray->pos), normal) / denom;
	if (t < EPSILON)
		return (get_zero_hit());
	hit_point = get_ray_pos_at_t(*ray, t);
	if (vectors_dot(sub_vectors(hit_point, center), sub_vectors(hit_point,
				center)) - radius2 > EPSILON)
		return (get_zero_hit());
	return (set_hit_info(t, ray));
}
