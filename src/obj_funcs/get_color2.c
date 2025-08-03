/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:27 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 00:11:03 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	is_checkerboard_fill_color(float *uv, float magnification)
{
	int		x_grid;
	int		y_grid;
	float	scaled_x;
	float	scaled_y;

	if (!uv)
		return (FALSE);
	if (magnification <= 0.0F)
		return (FALSE);
	scaled_x = uv[0] * CHECKERBOARD_SIZE * magnification;
	scaled_y = uv[1] * CHECKERBOARD_SIZE * magnification;
	x_grid = (int)floorf(scaled_x);
	y_grid = (int)floorf(scaled_y);
	return (((x_grid + y_grid) % 2) == 0);
}

t_color	get_sphere_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	ft_bzero(uv, sizeof(float) * 2);
	calc_sphere_uv_map_xy(obj, hit->pos, uv);
	if (is_checkerboard_fill_color(uv, 1.0F))
		color = get_opposite_color(color);
	return (color);
}

t_color	get_plane_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	ft_bzero(uv, sizeof(float) * 2);
	calc_plane_uv_map_xy(obj, hit->pos, uv);
	if (is_checkerboard_fill_color(uv, 0.001F))
		color = get_opposite_color(color);
	return (color);
}

t_color	get_cylinder_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	ft_bzero(uv, sizeof(float) * 2);
	calc_cylinder_uv_map_xy(obj, hit->pos, uv);
	if (is_checkerboard_fill_color(uv, 1.0F))
		color = get_opposite_color(color);
	return (color);
}

t_color	get_cone_checker_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	ft_bzero(uv, sizeof(float) * 2);
	calc_cone_uv_map_xy(obj, hit->pos, uv);
	if (is_checkerboard_fill_color(uv, 1.0F))
		color = get_opposite_color(color);
	return (color);
}
