/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:27:34 by katakada          #+#    #+#             */
/*   Updated: 2025/07/26 18:49:49 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 未実装
t_vector	calc_cylinder_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	normal = sub_vectors(hit->pos, obj->shape.cylinder.pos);
	return (normalize_vector(normal));
}

// 未実装
t_vector	calc_cylinder_bump_normal(t_obj *obj, t_hit *hit)
{
	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	return (calc_cylinder_normal(obj, hit));
}

// 未実装
t_vector	calc_cone_normal(t_obj *obj, t_hit *hit)
{
	t_vector	normal;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	normal = sub_vectors(hit->pos, obj->shape.cone.pos);
	return (normalize_vector(normal));
}

// 未実装
t_vector	calc_cone_bump_normal(t_obj *obj, t_hit *hit)
{
	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	return (calc_cone_normal(obj, hit));
}
