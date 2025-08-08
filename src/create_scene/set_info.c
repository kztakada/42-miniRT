/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:52:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/09 00:38:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_color(t_color *color, char *str_color)
{
	color->r = (float)ft_atoi(str_color);
	if (color->r < 0.0f || color->r > 255.0f)
		return (FAILURE);
	color->r = color->r / 255.0f;
	while (*str_color != ',')
		str_color++;
	str_color++;
	color->g = (float)ft_atoi(str_color);
	if (color->g < 0.0f || color->g > 255.0f)
		return (FAILURE);
	color->g = color->g / 255.0f;
	while (*str_color != ',')
		str_color++;
	str_color++;
	color->b = (float)ft_atoi(str_color);
	if (color->b < 0.0f || color->b > 255.0f)
		return (FAILURE);
	color->b = color->b / 255.0f;
	return (SUCCESS);
}

void	set_vector(t_vector *vector, char *str_vector)
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

void	set_material_default(t_obj *obj)
{
	obj->material.mirror = 0.0f;
	obj->material.specn = SPECULAR_CN_DEFAULT;
	obj->material.speckv = SPECULAR_KV_DEFAULT;
	obj->material.refract = 0.0f;
	obj->material.is_checkerboard = FALSE;
	obj->material.has_texture = FALSE;
	obj->material.has_bump = FALSE;
}
