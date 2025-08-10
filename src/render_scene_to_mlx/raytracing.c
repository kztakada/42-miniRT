/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:02:15 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 12:43:03 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_color	calc_lighting_color(t_lighting lighting, t_material *material)
{
	t_color	c;

	c.r = lighting.ambient.r + lighting.diffuse.r + lighting.specular.r;
	c.g = lighting.ambient.g + lighting.diffuse.g + lighting.specular.g;
	c.b = lighting.ambient.b + lighting.diffuse.b + lighting.specular.b;
	if (material && material->mirror > 0.0F)
		c = mix_colors_by_ratio(lighting.reflect, c, material->mirror);
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
		return (scene->bg_color);
	rt->hit.color = rt->closest_obj->get_color(rt->closest_obj, &rt->hit);
	rt->hit.normal = rt->closest_obj->calc_normal(rt->closest_obj, &rt->hit);
	calc_lights_effect(scene, rt, &lighting);
	--max_depth;
	if (rt->closest_obj->material.mirror > 0.0F && max_depth > 0)
		lighting.reflect = calc_reflect_color(scene, rt, max_depth);
	if (max_depth < 0)
		result_color = calc_lighting_color(lighting, NULL);
	else
		result_color = calc_lighting_color(lighting,
				&rt->closest_obj->material);
	return (result_color);
}

t_color	raytrace_at_dot(t_scene *scene, t_vector dot_pos)
{
	t_color			raytraced_color;
	t_raytracing	rt;

	rt.pov_ray.pos = scene->camera.pos;
	rt.pov_ray.dir = normalize_vector(sub_vectors(dot_pos, rt.pov_ray.pos));
	raytraced_color = raytracing(scene, &rt, MAX_RECURSION_DEPTH);
	return (raytraced_color);
}
