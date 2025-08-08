/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:39:20 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 00:56:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_rt_material(t_material *material)
{
	if (!material)
		return ;
	print_rgb_color(material->color);
	if (!material->is_bonus)
		return ;
	printf(" %f,%f,%f %f %d", material->mirror, material->specn,
		material->speckv, material->refract, material->is_checkerboard);
	if (material->has_texture && material->texture.file_path != NULL)
		printf(" %s", material->texture.file_path);
	else
		printf(" NULL");
	if (material->has_bump && material->bump.file_path != NULL)
		printf(" %s", material->bump.file_path);
	else
		printf(" NULL");
}

void	print_rt_sphere(t_obj *obj)
{
	if (!obj)
		return ;
	printf("sp %f,%f,%f %f", obj->shape.sphere.pos.x, obj->shape.sphere.pos.y,
		obj->shape.sphere.pos.z, obj->shape.sphere.diameter);
	print_rt_material(&obj->material);
	printf("\n");
}

void	print_rt_plane(t_obj *obj)
{
	if (!obj)
		return ;
	printf("pl %f,%f,%f %f,%f,%f", obj->shape.plane.pos.x,
		obj->shape.plane.pos.y, obj->shape.plane.pos.z, obj->shape.plane.dir.x,
		obj->shape.plane.dir.y, obj->shape.plane.dir.z);
	print_rt_material(&obj->material);
	printf("\n");
}

void	print_rt_cylinder(t_obj *obj)
{
	if (!obj)
		return ;
	printf("cy %f,%f,%f %f,%f,%f %f %f", obj->shape.cylinder.pos.x,
		obj->shape.cylinder.pos.y, obj->shape.cylinder.pos.z,
		obj->shape.cylinder.dir.x, obj->shape.cylinder.dir.y,
		obj->shape.cylinder.dir.z, obj->shape.cylinder.diameter,
		obj->shape.cylinder.height);
	print_rt_material(&obj->material);
	printf("\n");
}

void	print_rt_cone(t_obj *obj)
{
	if (!obj)
		return ;
	if (!obj->material.is_bonus)
		return ;
	printf("co %f,%f,%f %f,%f,%f %f %f %f", obj->shape.cone.pos.x,
		obj->shape.cone.pos.y, obj->shape.cone.pos.z, obj->shape.cone.dir.x,
		obj->shape.cone.dir.y, obj->shape.cone.dir.z, obj->shape.cone.h,
		obj->shape.cone.h2, obj->shape.cone.angle);
	print_rt_material(&obj->material);
	printf("\n");
}
