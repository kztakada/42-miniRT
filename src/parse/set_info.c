/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:52:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/05 04:15:52 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_color(t_color *color, char *str_color)
{
	color->r = ft_atof(str_color);
	if (color->r < 0.0f && color->r > 255.0f)
		return (FAILURE);
	color->r = color->r / 255.0f;
	while (*str_color != ',')
		str_color++;
	str_color++;
	color->g = ft_atof(str_color);
	if (color->g < 0.0f && color->g > 255.0f)
		return (FAILURE);
	color->g = color->g / 255.0f;
	while (*str_color != ',')
		str_color++;
	str_color++;
	color->b = ft_atof(str_color);
	if (color->b < 0.0f && color->b > 255.0f)
		return (FAILURE);
	color->b = color->b / 255.0f;
	return (SUCCESS);
}

t_binary_result	set_vector(t_vector *vector, char *str_vector)
{
	vector->x = ft_atof(str_vector);
	while (*str_vector != ',')
		str_vector++;
	str_vector++;
	vector->y = ft_atof(str_vector);
	while (*str_vector != ',')
		str_vector++;
	str_vector++;
	vector->z = ft_atof(str_vector);
	return (SUCCESS);
}

t_binary_result	set_spec_mirror(t_obj *obj, char *str)
{
	obj->material.mirror = ft_atof(str);
	if (obj->material.mirror < 0.0f || obj->material.mirror > 1.0f)
		return (FAILURE);
	while (*str != ',')
		str++;
	str++;
	obj->material.specn = ft_atof(str);
	if (obj->material.specn < 1.0f)
		return (FAILURE);
	while (*str != ',')
		str++;
	str++;
	obj->material.speckv = ft_atof(str);
	if (obj->material.speckv < 0.0f || obj->material.speckv > 1.0f)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	set_material_default(t_obj *obj)
{
	obj->material.mirror = 0.0f;
	obj->material.specn = 1.0f;
	obj->material.speckv = 0.2f;
	obj->material.refract =	0.0f;
	obj->material.is_checkerboard = FALSE;
	obj->material.has_texture = FALSE;
	obj->material.has_bump = FALSE;
	return (SUCCESS);
}
