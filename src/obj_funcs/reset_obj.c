/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:18:27 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 23:00:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_object_sphere(t_obj *obj)
{
	if (!obj)
		return ;
	obj->shape.sphere.pos = obj->shape.sphere.pos_initial;
	obj->shape.sphere.rotation_y = 0.0F;
	obj->shape.sphere.diameter = obj->shape.sphere.diameter_initial;
	obj->shape.sphere.radius_pow2 = obj->shape.sphere.diameter
		* obj->shape.sphere.diameter * 0.25f;
}

void	reset_object_plane(t_obj *obj)
{
	if (!obj)
		return ;
	obj->shape.plane.pos = obj->shape.plane.pos_initial;
	obj->shape.plane.dir = obj->shape.plane.dir_initial;
}

void	reset_object_cylinder(t_obj *obj)
{
	if (!obj)
		return ;
	obj->shape.cylinder.pos = obj->shape.cylinder.pos_initial;
	obj->shape.cylinder.dir = obj->shape.cylinder.dir_initial;
	obj->shape.cylinder.diameter = obj->shape.cylinder.diameter_initial;
	obj->shape.cylinder.height = obj->shape.cylinder.height_initial;
	obj->shape.cylinder.radius_pow2 = obj->shape.cylinder.diameter
		* obj->shape.cylinder.diameter * 0.25f;
}

void	reset_object_cone(t_obj *obj)
{
	if (!obj)
		return ;
	obj->shape.cone.pos = obj->shape.cone.pos_initial;
	obj->shape.cone.dir = obj->shape.cone.dir_initial;
	obj->shape.cone.h = obj->shape.cone.h_initial;
	obj->shape.cone.h2 = obj->shape.cone.h2_initial;
	obj->shape.cone.angle = obj->shape.cone.angle_initial;
	obj->shape.cone.cos2 = calc_cone_cos2(obj->shape.cone.angle);
}
