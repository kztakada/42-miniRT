/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:06:32 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 23:48:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	change_sphere_size(t_obj *obj, t_obj_size_type type)
{
	if (obj == NULL)
		return (FALSE);
	if (type == SIZE_HEIGHT_UP || type == SIZE_HEIGHT_DOWN)
		return (FALSE);
	if (type == SIZE_DIAMETER_UP)
		obj->shape.sphere.diameter += DIAMETER_STEP;
	else if (type == SIZE_DIAMETER_DOWN)
		obj->shape.sphere.diameter -= DIAMETER_STEP;
	obj->shape.sphere.radius_pow2 = obj->shape.sphere.diameter
		* obj->shape.sphere.diameter * 0.25f;
	return (TRUE);
}

t_bool	change_plane_size(t_obj *obj, t_obj_size_type type)
{
	(void)obj;
	(void)type;
	return (FALSE);
}

t_bool	change_cylinder_size(t_obj *obj, t_obj_size_type type)
{
	if (obj == NULL)
		return (FALSE);
	if (type == SIZE_DIAMETER_UP)
		obj->shape.cylinder.diameter += DIAMETER_STEP;
	else if (type == SIZE_DIAMETER_DOWN)
		obj->shape.cylinder.diameter -= DIAMETER_STEP;
	else if (type == SIZE_HEIGHT_UP)
		obj->shape.cylinder.height += HEIGHT_STEP;
	else if (type == SIZE_HEIGHT_DOWN)
		obj->shape.cylinder.height -= HEIGHT_STEP;
	obj->shape.cylinder.radius_pow2 = obj->shape.cylinder.diameter
		* obj->shape.cylinder.diameter * 0.25f;
	return (TRUE);
}

t_bool	change_cone_size(t_obj *obj, t_obj_size_type type)
{
	if (obj == NULL)
		return (FALSE);
	if (type == SIZE_DIAMETER_UP)
		obj->shape.cone.angle += CONE_ANGLE_STEP;
	else if (type == SIZE_DIAMETER_DOWN)
		obj->shape.cone.angle -= CONE_ANGLE_STEP;
	else if (type == SIZE_HEIGHT_UP)
	{
		obj->shape.cone.h += HEIGHT_STEP;
		obj->shape.cone.h2 += HEIGHT_STEP;
	}
	else if (type == SIZE_HEIGHT_DOWN)
	{
		obj->shape.cone.h -= HEIGHT_STEP;
		obj->shape.cone.h2 -= HEIGHT_STEP;
	}
	obj->shape.cone.cos2 = calc_cone_cos2(obj->shape.cone.angle);
	return (TRUE);
}
