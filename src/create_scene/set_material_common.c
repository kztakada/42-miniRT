/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:02:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/09 00:41:21 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_material_common(t_obj *obj, char **line_element, char *type)
{
	set_material_default(obj);
	if (set_color(&(obj->material.color), line_element[0]) == FAILURE)
		return (put_out_format_error(type, ERR_COLOR_ARG));
	if (!line_element[1])
		return (SUCCESS);
	else
	{
		if (set_spec_mirror(obj, line_element[1]) == FAILURE)
			return (put_out_format_error(type, ERR_SPECULAR_ARG));
		obj->material.refract = ft_atof(line_element[2]);
		if (obj->material.refract < 0.0f)
			return (put_out_format_error(type, ERR_REFRACT_ARG));
		if (obj->material.refract > 0.0f
			&& obj->material.refract < MIN_OBJ_REFRACT_INDEX)
			obj->material.refract = MIN_OBJ_REFRACT_INDEX;
	}
	return (SUCCESS);
}
