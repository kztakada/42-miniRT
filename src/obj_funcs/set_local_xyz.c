/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_xyz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:50:08 by katakada          #+#    #+#             */
/*   Updated: 2025/08/03 21:43:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_local_axes_common(t_obj *obj, t_vector *camera_dir)
{
	if (!obj || !camera_dir)
		return ;
	obj->local.x = cross_vector(obj->local.y, *camera_dir);
	obj->local.z = cross_vector(obj->local.x, obj->local.y);
	obj->local.x = normalize_vector(obj->local.x);
	obj->local.y = normalize_vector(obj->local.y);
	obj->local.z = normalize_vector(obj->local.z);
}

void	set_local_xyz_sphere(t_obj *obj, t_vector *camera_dir)
{
	if (!obj || !camera_dir)
		return ;
	obj->local.y = (t_vector){0.0F, 1.0F, 0.0F};
	set_local_axes_common(obj, camera_dir);
}

void	set_local_xyz_plane(t_obj *obj, t_vector *camera_dir)
{
	if (!obj || !camera_dir)
		return ;
	obj->local.y = obj->shape.plane.dir;
	set_local_axes_common(obj, camera_dir);
}

void	set_local_xyz_cylinder(t_obj *obj, t_vector *camera_dir)
{
	if (!obj || !camera_dir)
		return ;
	obj->local.y = obj->shape.cylinder.dir;
	set_local_axes_common(obj, camera_dir);
}

void	set_local_xyz_cone(t_obj *obj, t_vector *camera_dir)
{
	if (!obj || !camera_dir)
		return ;
	obj->local.y = obj->shape.cone.dir;
	set_local_axes_common(obj, camera_dir);
}
