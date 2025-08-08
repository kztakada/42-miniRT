/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_focused_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:13:38 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 23:06:08 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_material_info(t_material *material)
{
	if (!material)
		return ;
	printf("\nMaterial Info:\n");
	print_rgb_color_info(material->color);
	printf("  Mirror: %f\n", material->mirror);
	printf("  speckv: %f\n", material->speckv);
	printf("  specn: %f\n", material->specn);
	printf("  Refraction: %f\n", material->refract);
	if (material->has_texture)
		printf("Texture: %s\n", material->texture.file_path);
	if (material->has_bump)
		printf("Bump Map: %s\n", material->bump.file_path);
}

void	print_focused_obj_sphere(t_obj *obj)
{
	if (!obj)
		return ;
	printf("\nSphere Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.sphere.pos.x,
		obj->shape.sphere.pos.y, obj->shape.sphere.pos.z);
	printf("  Diameter: %f\n", obj->shape.sphere.diameter);
	printf("  Rotation y: %f\n\n\n", obj->shape.sphere.rotation_y);
	print_material_info(&obj->material);
}

void	print_focused_obj_plane(t_obj *obj)
{
	if (!obj)
		return ;
	printf("\nPlane Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.plane.pos.x,
		obj->shape.plane.pos.y, obj->shape.plane.pos.z);
	printf("  Direction: (%f, %f, %f)\n\n\n\n", obj->shape.plane.dir.x,
		obj->shape.plane.dir.y, obj->shape.plane.dir.z);
	print_material_info(&obj->material);
}

void	print_focused_obj_cylinder(t_obj *obj)
{
	if (!obj)
		return ;
	printf("\nCylinder Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.cylinder.pos.x,
		obj->shape.cylinder.pos.y, obj->shape.cylinder.pos.z);
	printf("  Direction: (%f, %f, %f)\n", obj->shape.cylinder.dir.x,
		obj->shape.cylinder.dir.y, obj->shape.cylinder.dir.z);
	printf("  Height: %f\n", obj->shape.cylinder.height);
	printf("  Diameter: %f\n\n", obj->shape.cylinder.diameter);
	print_material_info(&obj->material);
}

void	print_focused_obj_cone(t_obj *obj)
{
	if (!obj)
		return ;
	printf("\nCone Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.cone.pos.x,
		obj->shape.cone.pos.y, obj->shape.cone.pos.z);
	printf("  Direction: (%f, %f, %f)\n", obj->shape.cone.dir.x,
		obj->shape.cone.dir.y, obj->shape.cone.dir.z);
	printf("  Angle: %f\n", obj->shape.cone.angle);
	printf("  Height1: %f\n", obj->shape.cone.h);
	printf("  Height2: %f\n", obj->shape.cone.h2);
	print_material_info(&obj->material);
}
