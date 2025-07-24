/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:02:15 by katakada          #+#    #+#             */
/*   Updated: 2025/07/25 00:27:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*calc_closest_obj(t_list *objs, t_ray *pov_ray, t_hit *hit)
{
	t_obj	*closest_obj;
	float	min_t;
	t_hit	collision;

	closest_obj = NULL;
	min_t = FLT_MAX;
	while (objs)
	{
		collision.is_hit = FALSE;
		collision.t = -1.0F;
		collision = get_obj(objs)->calc_obj_hit(get_obj(objs), pov_ray);
		if (collision.is_hit && collision.t > EPSILON && collision.t < min_t)
		{
			min_t = collision.t;
			closest_obj = get_obj(objs);
			if (hit != NULL)
				*hit = collision;
		}
		objs = objs->next;
	}
	return (closest_obj);
}

static t_color	calc_reflect_color(t_scene *scene, t_raytracing *rt,
		int max_depth)
{
	t_raytracing	reflect_rt;
	t_vector		reflect_dir;
	t_vector		offset_pos;

	reflect_dir = normalize_vector(calc_reflection_vector(rt->pov_ray.dir,
				rt->hit.normal));
	offset_pos = add_vectors(rt->hit.pos, scale_vector(EPSILON,
				rt->hit.normal));
	reflect_rt.pov_ray.pos = offset_pos;
	reflect_rt.pov_ray.dir = reflect_dir;
	return (raytracing(scene, &reflect_rt, max_depth));
}

static t_color	calc_refract_color(t_scene *scene, t_raytracing *rt,
		int max_depth)
{
	t_raytracing	refract_rt;
	t_vector		refract_dir;
	t_vector		offset_pos;
	float			incident_angle;

	// 媒質の屈折率を決定　　←パース時に実装する
	// 	obj_refract = rt->closest_obj->material.refract;
	// if (obj_refract < MIN_OBJ_REFRACT_INDEX)
	// 	obj_refract = MIN_OBJ_REFRACT_INDEX;
	// 入射角を計算して内側・外側を判定
	incident_angle = vectors_dot(rt->pov_ray.dir, rt->hit.normal);
	// 屈折ベクトルを計算
	if (incident_angle < 0.0F)
		refract_dir = calc_refraction_vector(rt->pov_ray.dir, rt->hit.normal,
				rt->refract_index, rt->closest_obj->material.refract);
	else
		refract_dir = calc_refraction_vector(rt->pov_ray.dir, rt->hit.normal,
				rt->closest_obj->material.refract, rt->refract_index);
	// 全反射の場合
	if (vector_len(refract_dir) < EPSILON)
		return ((t_color){0.0f, 0.0f, 0.0f});
	refract_dir = normalize_vector(refract_dir);
	// 屈折レイの開始点（自己交差回避）
	offset_pos = add_vectors(rt->hit.pos, scale_vector(EPSILON, refract_dir));
	refract_rt.pov_ray.pos = offset_pos;
	refract_rt.pov_ray.dir = refract_dir;
	// 屈折後の媒質の屈折率を設定
	if (incident_angle < 0.0F)
		refract_rt.refract_index = rt->closest_obj->material.refract;
	// 外側から内側への屈折
	else
		refract_rt.refract_index = AIR_REFRACT_INDEX; // 内側から外側への屈折
	return (raytracing(scene, &refract_rt, max_depth));
}

static t_color	calc_lighting_color(t_lighting lighting, t_material *material)
{
	t_color	c;

	c.r = lighting.ambient.r + lighting.diffuse.r + lighting.specular.r;
	c.g = lighting.ambient.g + lighting.diffuse.g + lighting.specular.g;
	c.b = lighting.ambient.b + lighting.diffuse.b + lighting.specular.b;
	if (material && material->mirror > 0.0F)
		c = mix_colors_by_ratio(lighting.reflect, c, material->mirror);
	if (material && material->refract > 0.0F)
		c = mix_colors_by_ratio(lighting.refract, c, 0.7F);
	c.r = fminf(c.r, 1.0F);
	c.g = fminf(c.g, 1.0F);
	c.b = fminf(c.b, 1.0F);
	return (c);
}

t_color	raytracing(t_scene *scene, t_raytracing *rt, int max_depth)
{
	t_lighting	lighting;
	t_color		result_color;

	ft_memset(&lighting, 0, sizeof(t_lighting));
	rt->closest_obj = calc_closest_obj(scene->objs, &rt->pov_ray, &rt->hit);
	if (rt->closest_obj == NULL)
		return ((t_color){BG_COLOR_R, BG_COLOR_G, BG_COLOR_B});
	rt->hit.color = rt->closest_obj->get_color(rt->closest_obj, &rt->hit);
	rt->hit.normal = rt->closest_obj->calc_normal(rt->closest_obj, &rt->hit);
	// if (rt->closest_obj->material.has_bump) ←ここはいらない（パースの時点で、バンプを持っていたら、calc_normalを差し替える）
	// 	calc_bump_normal(rt->closest_obj, &rt->hit);
	calc_lights_effect(scene, rt, &lighting);
	--max_depth;
	if (rt->closest_obj->material.mirror > 0.0F && max_depth > 0)
		lighting.reflect = calc_reflect_color(scene, rt, max_depth);
	if (rt->closest_obj->material.refract > 0.0F && max_depth > 0)
		lighting.refract = calc_refract_color(scene, rt, max_depth);
	if (max_depth < 0)
		result_color = calc_lighting_color(lighting, NULL);
	else
		result_color = calc_lighting_color(lighting,
				&rt->closest_obj->material);
	return (result_color);
}
