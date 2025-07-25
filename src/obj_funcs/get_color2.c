/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:27 by katakada          #+#    #+#             */
/*   Updated: 2025/07/26 22:08:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 未実装
t_color	get_cylinder_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_cylinder_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_cone_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}

// 未実装
t_color	get_cone_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	return (color);
}
