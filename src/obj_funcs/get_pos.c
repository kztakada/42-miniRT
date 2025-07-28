/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:11:24 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 19:16:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*get_sphere_pos(t_obj *obj)
{
	t_vector	*obj_pos;

	if (!obj)
		return (NULL);
	obj_pos = &(obj->shape.sphere.pos);
	return (obj_pos);
}

t_vector	*get_plane_pos(t_obj *obj)
{
	t_vector	*obj_pos;

	if (!obj)
		return (NULL);
	obj_pos = &(obj->shape.plane.pos);
	return (obj_pos);
}

t_vector	*get_cylinder_pos(t_obj *obj)
{
	t_vector	*obj_pos;

	if (!obj)
		return (NULL);
	obj_pos = &(obj->shape.cylinder.pos);
	return (obj_pos);
}

t_vector	*get_cone_pos(t_obj *obj)
{
	t_vector	*obj_pos;

	if (!obj)
		return (NULL);
	obj_pos = &(obj->shape.cone.pos);
	return (obj_pos);
}
