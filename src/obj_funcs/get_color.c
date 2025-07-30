/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:10 by katakada          #+#    #+#             */
/*   Updated: 2025/07/26 22:08:32 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_sphere_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_sphere_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_plane_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_plane_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}
