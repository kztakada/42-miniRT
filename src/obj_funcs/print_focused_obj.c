/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_focused_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:13:38 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 13:52:33 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_focused_obj_sphere(t_obj *obj)
{
	if (!obj)
		return ;
	printf("Sphere Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.sphere.pos.x,
		obj->shape.sphere.pos.y, obj->shape.sphere.pos.z);
	printf("  Diameter: %f\n", obj->shape.sphere.diameter);
	printf("  Color: (%f, %f, %f)\n", obj->material.color.r,
		obj->material.color.g, obj->material.color.b);
	printf("  Rotation y: %f\n", obj->shape.sphere.rotation_y);
}

void	print_focused_obj_plane(t_obj *obj)
{
	if (!obj)
		return ;
	printf("Plane Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.plane.pos.x,
		obj->shape.plane.pos.y, obj->shape.plane.pos.z);
	printf("  Direction: (%f, %f, %f)\n", obj->shape.plane.dir.x,
		obj->shape.plane.dir.y, obj->shape.plane.dir.z);
	printf("  Color: (%f, %f, %f)\n", obj->material.color.r,
		obj->material.color.g, obj->material.color.b);
}

void	print_focused_obj_cylinder(t_obj *obj)
{
	if (!obj)
		return ;
	printf("Cylinder Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.cylinder.pos.x,
		obj->shape.cylinder.pos.y, obj->shape.cylinder.pos.z);
	printf("  Direction: (%f, %f, %f)\n", obj->shape.cylinder.dir.x,
		obj->shape.cylinder.dir.y, obj->shape.cylinder.dir.z);
	printf("  Height: %f\n", obj->shape.cylinder.height);
	printf("  Diameter: %f\n", obj->shape.cylinder.diameter);
	printf("  Color: (%f, %f, %f)\n", obj->material.color.r,
		obj->material.color.g, obj->material.color.b);
}

void	print_focused_obj_cone(t_obj *obj)
{
	if (!obj)
		return ;
	printf("Cone Object:\n");
	printf("  Position: (%f, %f, %f)\n", obj->shape.cone.pos.x,
		obj->shape.cone.pos.y, obj->shape.cone.pos.z);
	printf("  Height: %f\n", obj->shape.cone.h);
	printf("  Color: (%f, %f, %f)\n", obj->material.color.r,
		obj->material.color.g, obj->material.color.b);
}
