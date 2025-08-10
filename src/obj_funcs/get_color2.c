/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:07:27 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:30:57 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_texture_color_by_uv(t_texture *texture, float *uv)
{
	size_t	tex_x;
	size_t	tex_y;
	size_t	i;

	if (!texture || !texture->color || !uv)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	// UV座標をテクスチャ座標に変換（境界処理付き）
	tex_x = (size_t)(uv[0] * (texture->width - 1) + 0.5f);
	tex_y = (size_t)(uv[1] * (texture->height - 1) + 0.5f);
	// 境界クランプ処理
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	i = tex_x + tex_y * texture->width;
	if (i >= texture->width * texture->height)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	return (texture->color[i]);
}

t_color	get_sphere_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	// テクスチャがない場合は基本色を返す
	if (!obj->material.texture.color)
		return (obj->material.color);
	ft_bzero(uv, sizeof(float) * 2);
	calc_sphere_uv_map_equirectangular(obj, hit->pos, uv,
		obj->shape.sphere.rotation_y);
	color = get_texture_color_by_uv(&obj->material.texture, uv);
	return (color);
}

t_color	get_plane_texture_color(t_obj *obj, t_hit *hit)
{
	t_color	color;
	float	uv[2];

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	// テクスチャがない場合は基本色を返す
	if (!obj->material.texture.color)
		return (obj->material.color);
	ft_bzero(uv, sizeof(float) * 2);
	calc_plane_uv_map_tiling(obj, hit->pos, uv);
	color = get_texture_color_by_uv(&obj->material.texture, uv);
	return (color);
}

t_color	get_cylinder_texture_color(t_obj *obj, t_hit *hit)
{
	t_color		color;
	float		uv[2];
	t_vector	local_pos;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	// テクスチャがない場合は基本色を返す
	if (!obj->material.texture.color)
		return (obj->material.color);
	// ワールド座標をローカル座標に変換
	local_pos = sub_vectors(hit->pos, obj->shape.cylinder.pos);
	ft_bzero(uv, sizeof(float) * 2);
	calc_stretch_mapping_uv(local_pos, obj->shape.cylinder.dir,
		obj->shape.cylinder.height, uv);
	color = get_texture_color_by_uv(&obj->material.texture, uv);
	return (color);
}

t_color	get_cone_texture_color(t_obj *obj, t_hit *hit)
{
	t_color		color;
	float		uv[2];
	t_vector	local_pos;
	float		axis_projection;

	if (!obj || !hit)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	if (!obj->material.texture.color)
		return (obj->material.color);
	local_pos = sub_vectors(hit->pos, obj->shape.cone.pos);
	ft_bzero(uv, sizeof(float) * 2);
	axis_projection = vectors_dot(local_pos, obj->shape.cone.dir);
	calc_cone_stretch_mapping_uv(&obj->shape.cone, axis_projection, local_pos,
		uv);
	color = get_texture_color_by_uv(&obj->material.texture, uv);
	return (color);
}
