/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:10 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 19:33:32 by katakada         ###   ########.fr       */
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

t_color	get_sphere_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];
	size_t	i;
	size_t	tex_x;
	size_t	tex_y;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.color;
	ft_bzero(uv, sizeof(float) * 2);
	calc_sphere_uv_map_equirectangular(obj, hit->pos, uv,
		obj->shape.sphere.rotation_y);
	// UV座標をテクスチャ座標に変換（境界処理付き）
	tex_x = (size_t)(uv[0] * (obj->material.texture.width - 1) + 0.5f);
	tex_y = (size_t)(uv[1] * (obj->material.texture.height - 1) + 0.5f);
	// 境界クランプ処理
	if (tex_x >= obj->material.texture.width)
		tex_x = obj->material.texture.width - 1;
	if (tex_y >= obj->material.texture.height)
		tex_y = obj->material.texture.height - 1;
	i = tex_x + tex_y * obj->material.texture.width;
	if (i >= obj->material.texture.width * obj->material.texture.height)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	color = obj->material.texture.color[i];
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
t_color	get_cylinder_texture_color(t_obj *obj, t_hit *hit)
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
