/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lights_effect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:41:51 by katakada          #+#    #+#             */
/*   Updated: 2025/07/24 23:42:07 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_to_light_src_ray(t_raytracing *rt, t_light *light)
{
	t_vector	offset_pos;

	offset_pos = add_vectors(rt->hit.pos, scale_vector(EPSILON,
				rt->hit.normal));
	rt->to_light_src_ray.pos = offset_pos;
	rt->to_light_src_ray.dir = normalize_vector(sub_vectors(light->pos,
				offset_pos));
}

static t_bool	has_light_blocking(t_scene *scene, t_raytracing *rt,
		t_light *light)
{
	t_obj	*collision_obj;
	float	distance_to_light;
	float	distance_to_blocking_obj;

	collision_obj = calc_closest_obj(scene->objs, &rt->to_light_src_ray,
			&rt->blocking_hit);
	if (collision_obj == NULL)
		return (FALSE);
	distance_to_light = calc_distance(rt->to_light_src_ray.pos, light->pos);
	distance_to_blocking_obj = calc_distance(rt->to_light_src_ray.pos,
			rt->blocking_hit.pos);
	if (distance_to_blocking_obj > distance_to_light)
		return (FALSE);
	else
		return (TRUE);
}

static t_color	calc_diffuse_light(t_raytracing *rt, t_light *light,
		float incident_intensity)
{
	t_color	diffuse_color;

	if (incident_intensity <= 0.0F)
		return ((t_color){0.0F, 0.0F, 0.0F});
	diffuse_color = add_lighting(rt->hit.color, light->color, light->brightness
			* incident_intensity);
	return (diffuse_color);
}

// using the Blinn-Phong reflection model
// static t_color	calc_specular_light(t_raytracing *rt, t_light *light,
// 		float incident_intensity)
// {
// 	t_vector	to_light_dir;
// 	t_vector	to_camera_dir;
// 	t_vector	half_vector_dir;
// 	float		specular_intensity;
// 	t_color		specular_color;

// 	if (incident_intensity <= 0.0F)
// 		return ((t_color){0.0F, 0.0F, 0.0F});
// 	to_light_dir = rt->to_light_src_ray.dir;
// 	to_camera_dir = normalize_vector(sub_vectors(rt->pov_ray.pos, rt->hit.pos));
// 	half_vector_dir = normalize_vector(add_vectors(to_light_dir,
// 				to_camera_dir));
// 	specular_intensity = vectors_dot(half_vector_dir, rt->hit.normal);
// 	if (specular_intensity <= 0.0F)
// 		return ((t_color){0.0F, 0.0F, 0.0F});
// 	specular_intensity = powf(specular_intensity,
// 			rt->closest_obj->material.specn) * rt->closest_obj->material.speckv;
// 	specular_color = add_lighting((t_color){1.0F, 1.0F, 1.0F}, light->color,
// 			light->brightness * specular_intensity);
// 	return (specular_color);
// }

static t_color	calc_specular_light_phong(t_raytracing *rt, t_light *light,
		float incident_intensity)
{
	t_vector	incident_dir;
	t_vector	reflect_dir;
	t_vector	to_camera_dir;
	float		specular_intensity;
	t_color		specular_color;

	if (incident_intensity <= 0.0f)
		return ((t_color){0.0f, 0.0f, 0.0f});
	incident_dir = inverse_vector(rt->to_light_src_ray.dir);
	reflect_dir = calc_reflection_vector(incident_dir, rt->hit.normal);
	to_camera_dir = normalize_vector(sub_vectors(rt->pov_ray.pos, rt->hit.pos));
	specular_intensity = vectors_dot(reflect_dir, to_camera_dir);
	if (specular_intensity <= 0.0f)
		return ((t_color){0.0f, 0.0f, 0.0f});
	specular_intensity = powf(specular_intensity,
			rt->closest_obj->material.specn) * rt->closest_obj->material.speckv;
	specular_color = add_lighting((t_color){1.0F, 1.0F, 1.0F}, light->color,
			light->brightness * specular_intensity);
	return (specular_color);
}

void	calc_lights_effect(t_scene *scene, t_raytracing *rt,
		t_lighting *lighting)
{
	t_list	*lights;
	float	light_intensity;
	t_color	delta_c;

	lighting->ambient = add_lighting(rt->hit.color, scene->ambient.color,
			scene->ambient.brightness);
	lights = scene->lights;
	while (lights)
	{
		set_to_light_src_ray(rt, get_light(lights));
		light_intensity = vectors_dot(rt->to_light_src_ray.dir, rt->hit.normal);
		if (light_intensity > 0.0f)
		{
			if (!has_light_blocking(scene, rt, get_light(lights)))
			{
				delta_c = calc_diffuse_light(rt, get_light(lights),
						light_intensity);
				lighting->diffuse = add_colors(lighting->diffuse, delta_c);
				delta_c = calc_specular_light_phong(rt, get_light(lights),
						light_intensity);
				lighting->specular = add_colors(lighting->specular, delta_c);
			}
		}
		lights = lights->next;
	}
}
