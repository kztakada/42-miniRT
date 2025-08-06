/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:12:46 by katakada          #+#    #+#             */
/*   Updated: 2025/08/06 00:28:59 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	calc_sphere_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	normal = sub_vectors(hit->pos, obj->shape.sphere.pos);
	return (normalize_vector(normal));
}

t_vector	calc_plane_normal(t_obj *obj, t_hit *hit)
{
	float	incident_angle;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	incident_angle = vectors_dot(hit->pov_dir, obj->shape.plane.dir);
	if (incident_angle < 0.0F)
		return (obj->shape.plane.dir);
	else
		return (inverse_vector(obj->shape.plane.dir));
}


