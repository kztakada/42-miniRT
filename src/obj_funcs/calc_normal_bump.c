/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_normal_bump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:20:38 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 21:11:11 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pos2d	get_texture_pos_by_uv(t_material material, float *uv)
{
	t_pos2d	tex_pos;

	tex_pos.x = (int)(uv[0] * (material.bump.width - 1) + 0.5f);
	tex_pos.y = (int)(uv[1] * (material.bump.height - 1) + 0.5f);
	tex_pos.x = clamp_int(tex_pos.x, 0, material.bump.width - 1);
	tex_pos.y = clamp_int(tex_pos.y, 0, material.bump.height - 1);
	return (tex_pos);
}

// latitude_factor = cosf(latitude)		latitude: -π/2 ~ π/2
t_vector	calc_sphere_bump_normal(t_obj *obj, t_hit *hit)
{
	float	uv[2];
	float	latitude_factor;
	t_pos2d	bump_dot;
	t_uv	bump_delta;
	t_uv	ref_scale;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	hit->normal = calc_sphere_normal(obj, hit);
	ft_bzero(uv, sizeof(float) * 2);
	calc_sphere_uv_map_equirectangular(obj, hit->pos, uv,
		obj->shape.sphere.rotation_y);
	latitude_factor = cosf((uv[1] - 0.5F) * (float)M_PI);
	if (latitude_factor < 0.1F)
		latitude_factor = 0.1F;
	bump_dot = get_texture_pos_by_uv(obj->material, uv);
	ref_scale.u = 1.0F / latitude_factor;
	ref_scale.v = 1.0F;
	bump_delta = calc_bump_effects(obj, bump_dot, ref_scale);
	bump_delta.u *= latitude_factor;
	return (calc_bumped_normal(obj, hit->normal, bump_delta));
}

t_vector	calc_plane_bump_normal(t_obj *obj, t_hit *hit)
{
	float	uv[2];
	t_pos2d	bump_dot;
	t_uv	bump_delta;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	hit->normal = calc_plane_normal(obj, hit);
	ft_bzero(uv, sizeof(float) * 2);
	calc_plane_uv_map_tiling(obj, hit->pos, uv);
	bump_dot = get_texture_pos_by_uv(obj->material, uv);
	bump_delta = calc_bump_effects(obj, bump_dot, (t_uv){1.0F, 1.0F});
	return (calc_bumped_normal(obj, hit->normal, bump_delta));
}

t_vector	calc_cylinder_bump_normal(t_obj *obj, t_hit *hit)
{
	float		uv[2];
	t_pos2d		bump_dot;
	t_uv		bump_delta;
	t_vector	local_pos;
	float		axis_projection;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	hit->normal = calc_cylinder_normal(obj, hit);
	ft_bzero(uv, sizeof(float) * 2);
	local_pos = sub_vectors(hit->pos, obj->shape.cylinder.pos);
	axis_projection = vectors_dot(local_pos, obj->shape.cylinder.dir);
	if (fabsf(axis_projection - obj->shape.cylinder.height) < EPSILON)
		return (obj->shape.cylinder.dir);
	if (fabsf(axis_projection) < EPSILON)
		return (inverse_vector(obj->shape.cylinder.dir));
	calc_stretch_mapping_uv(local_pos, obj->shape.cylinder.dir,
		obj->shape.cylinder.height, uv);
	bump_dot = get_texture_pos_by_uv(obj->material, uv);
	bump_delta = calc_bump_effects(obj, bump_dot, (t_uv){1.0F, 1.0F});
	return (calc_bumped_normal(obj, hit->normal, bump_delta));
}

t_vector	calc_cone_bump_normal(t_obj *obj, t_hit *hit)
{
	float		uv[2];
	t_pos2d		bump_dot;
	t_uv		bump_delta;
	t_vector	local_pos;
	float		axis_projection;

	if (!obj || !hit)
		return (put_out_error_vector(ERR_INVALID_CN_ARGS));
	hit->normal = calc_cone_normal(obj, hit);
	ft_bzero(uv, sizeof(float) * 2);
	local_pos = sub_vectors(hit->pos, obj->shape.cone.pos);
	axis_projection = vectors_dot(local_pos, obj->shape.cone.dir);
	if (axis_projection > 0.0F && fabsf(axis_projection
			- obj->shape.cone.h) < EPSILON)
		return (obj->shape.cone.dir);
	if (axis_projection < 0.0F && fabsf(axis_projection
			+ obj->shape.cone.h2) < EPSILON)
		return (inverse_vector(obj->shape.cone.dir));
	calc_cone_stretch_mapping_uv(&obj->shape.cone, axis_projection, local_pos,
		uv);
	bump_dot = get_texture_pos_by_uv(obj->material, uv);
	bump_delta = calc_bump_effects(obj, bump_dot, (t_uv){1.0F, 1.0F});
	return (calc_bumped_normal(obj, hit->normal, bump_delta));
}
