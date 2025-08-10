/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:27:34 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:31:50 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	calc_cylinder_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;
	t_cylinder	*cyl;
	t_vector	center_to_hit;
	float		dist_along_axis;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	cyl = &obj->shape.cylinder;
	center_to_hit = sub_vectors(hit->pos, cyl->pos);
	dist_along_axis = vectors_dot(center_to_hit, cyl->dir);
	if (fabsf(dist_along_axis) < EPSILON)
		return (inverse_vector(cyl->dir));
	if (fabsf(dist_along_axis - cyl->height) < EPSILON)
		return (cyl->dir);
	normal = sub_vectors(center_to_hit, scale_vector(dist_along_axis,
				cyl->dir));
	return (normalize_vector(normal));
}

static t_vector	calc_cone_side_normal(float dist_along_axis,
		t_vector tip_to_hit, t_cone *cone, t_hit *hit)
{
	float		scalar;
	t_vector	cone_dir;
	t_vector	axis_proj;
	t_vector	normal;

	scalar = vector_len(tip_to_hit) / cosf(cone->angle / 2.0f);
	cone_dir = cone->dir;
	if (dist_along_axis < 0)
		cone_dir = inverse_vector(cone->dir);
	axis_proj = add_vectors(cone->pos, scale_vector(scalar, cone_dir));
	normal = sub_vectors(hit->pos, axis_proj);
	return (normal);
}

t_vector	calc_cone_normal(t_obj *obj, t_hit *hit)
{
	t_cone		*cone;
	t_vector	normal;
	t_vector	tip_to_hit;
	float		dist_along_axis;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	cone = &obj->shape.cone;
	tip_to_hit = sub_vectors(hit->pos, cone->pos);
	dist_along_axis = vectors_dot(tip_to_hit, cone->dir);
	if (dist_along_axis > 0 && fabsf(dist_along_axis - cone->h) < EPSILON)
		return (cone->dir);
	if (dist_along_axis < 0 && fabsf(dist_along_axis + cone->h2) < EPSILON)
		return (inverse_vector(cone->dir));
	normal = calc_cone_side_normal(dist_along_axis, tip_to_hit, cone, hit);
	return (normalize_vector(normal));
}
