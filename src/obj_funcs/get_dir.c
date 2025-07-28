/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:17:05 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 19:26:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*get_sphere_dir(t_obj *obj __attribute__((unused)))
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd("shape sphere does not have a direction.\n", STDERR_FILENO);
	return (NULL);
}

t_vector	*get_plane_dir(t_obj *obj)
{
	t_vector	*obj_dir;

	if (!obj)
		return (NULL);
	obj_dir = &(obj->shape.plane.dir);
	return (obj_dir);
}

t_vector	*get_cylinder_dir(t_obj *obj)
{
	t_vector	*obj_dir;

	if (!obj)
		return (NULL);
	obj_dir = &(obj->shape.cylinder.dir);
	return (obj_dir);
}

t_vector	*get_cone_dir(t_obj *obj)
{
	t_vector	*obj_dir;

	if (!obj)
		return (NULL);
	obj_dir = &(obj->shape.cone.dir);
	return (obj_dir);
}
