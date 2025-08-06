/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material_common.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:02:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/05 21:54:56 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_material_common(t_obj *obj, char **line_element,
		int start_index)
{
	if (set_spec_mirror(obj, line_element[start_index + 1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	obj->material.refract = ft_atof(line_element[start_index + 2]);
	if (obj->material.refract < 0.0f)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	if (obj->material.refract > 0.0f
		&& obj->material.refract < MIN_OBJ_REFRACT_INDEX)
		obj->material.refract = MIN_OBJ_REFRACT_INDEX;
	return (SUCCESS);
}
