/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:26:56 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:46:34 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_sphere_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	target_dir;
	t_vector	local_pos;
	float		phi;
	float		theta;

	if (!obj || !uv_map)
		return ;
	target_dir = normalize_vector(sub_vectors(target_pos,
				obj->shape.sphere.pos));
	local_pos.x = vectors_dot(target_dir, obj->local.x);
	local_pos.y = vectors_dot(target_dir, obj->local.y);
	local_pos.z = vectors_dot(target_dir, obj->local.z);
	theta = acosf(clampf(local_pos.y, -1.0f, 1.0f));
	phi = atan2f(local_pos.z, local_pos.x);
	uv_map[0] = (phi + M_PI) / (2.0f * M_PI);
	uv_map[1] = theta / M_PI;
	if (uv_map[0] < 0.0f)
		uv_map[0] += 1.0f;
	if (uv_map[0] > 1.0f)
		uv_map[0] -= 1.0f;
	uv_map[0] = clampf(uv_map[0], 0.0f, 1.0f);
	uv_map[1] = clampf(uv_map[1], 0.0f, 1.0f);
}

void	calc_sphere_uv_map_equirectangular(t_obj *obj, t_vector hit_pos,
		float *uv, float rotation_y)
{
	t_vector	local_point;
	float		phi;
	float		theta;

	if (!obj || !uv)
		return ;
	if (obj->shape.sphere.diameter / 2.0F < EPSILON)
	{
		uv[0] = 0.5F;
		uv[1] = 0.5F;
		return ;
	}
	local_point = normalize_vector(sub_vectors(hit_pos, obj->shape.sphere.pos));
	theta = acosf(clampf(local_point.y, -1.0f, 1.0f));
	phi = atan2f(local_point.z, local_point.x);
	phi += rotation_y * (float)M_PI;
	uv[0] = (phi + M_PI) / (2.0f * M_PI);
	uv[1] = theta / M_PI;
	uv[0] = fmod(uv[0], 1.0f);
	if (uv[0] < 0.0f)
		uv[0] += 1.0f;
	uv[0] = 1.0f - uv[0];
	uv[0] = clampf(uv[0], 0.0f, 1.0f);
	uv[1] = clampf(uv[1], 0.0f, 1.0f);
}

void	calc_plane_uv_map_xy(t_obj *obj, t_vector target_pos, float *uv_map)
{
	t_vector	relative_pos;

	if (!obj || !uv_map)
		return ;
	relative_pos = sub_vectors(target_pos, obj->shape.plane.pos);
	uv_map[0] = vectors_dot(relative_pos, obj->local.x);
	uv_map[1] = vectors_dot(relative_pos, obj->local.z);
}

void	generate_orthogonal_axes(t_vector normal, t_vector *axis_x,
		t_vector *axis_y)
{
	t_vector	up;
	t_vector	right;

	up = (t_vector){0, 1, 0};
	right = (t_vector){1, 0, 0};
	if (fabsf(vectors_dot(normal, up)) > 0.9f)
		*axis_x = normalize_vector(cross_vector(normal, right));
	else
		*axis_x = normalize_vector(cross_vector(normal, up));
	*axis_y = normalize_vector(cross_vector(normal, *axis_x));
}

void	calc_plane_uv_map_tiling(t_obj *obj, t_vector target_pos, float *uv)
{
	t_vector	local_pos;
	t_vector	axis_x;
	t_vector	axis_y;

	generate_orthogonal_axes(obj->shape.plane.dir, &axis_x, &axis_y);
	local_pos = sub_vectors(target_pos, obj->shape.plane.pos);
	uv[0] = vectors_dot(local_pos, axis_x) * TEXTURE_TILE_SCALE + 0.5f;
	uv[1] = vectors_dot(local_pos, axis_y) * TEXTURE_TILE_SCALE + 0.5f;
	uv[0] = uv[0] - floorf(uv[0]);
	uv[1] = uv[1] - floorf(uv[1]);
	if (uv[0] < 0)
		uv[0] += 1.0f;
	if (uv[1] < 0)
		uv[1] += 1.0f;
}
