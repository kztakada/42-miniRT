/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:17:05 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 19:13:53 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_dir	get_sphere_dir(t_obj *obj __attribute__((unused)))
{
	t_obj_dir	obj_dir;

	obj_dir.type = UV_DIR;
	obj_dir.dir = NULL;
	obj_dir.rotate_y = NULL;
	if (!obj)
		return (obj_dir);
	obj_dir.rotate_y = &(obj->shape.sphere.rotation_y);
	return (obj_dir);
}

t_obj_dir	get_plane_dir(t_obj *obj)
{
	t_obj_dir	obj_dir;

	obj_dir.type = VECTOR_DIR;
	obj_dir.dir = NULL;
	obj_dir.rotate_y = NULL;
	if (!obj)
		return (obj_dir);
	obj_dir.dir = &(obj->shape.plane.dir);
	return (obj_dir);
}

t_obj_dir	get_cylinder_dir(t_obj *obj)
{
	t_obj_dir	obj_dir;

	obj_dir.type = VECTOR_DIR;
	obj_dir.dir = NULL;
	obj_dir.rotate_y = NULL;
	if (!obj)
		return (obj_dir);
	obj_dir.dir = &(obj->shape.cylinder.dir);
	return (obj_dir);
}

t_obj_dir	get_cone_dir(t_obj *obj)
{
	t_obj_dir	obj_dir;

	obj_dir.type = VECTOR_DIR;
	obj_dir.dir = NULL;
	obj_dir.rotate_y = NULL;
	if (!obj)
		return (obj_dir);
	obj_dir.dir = &(obj->shape.cone.dir);
	return (obj_dir);
}
