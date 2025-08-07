/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:02:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/05 04:17:13 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_material(t_obj *obj, char **line_element, int start_index)
{
	if (set_color(&(obj->material.color), line_element[start_index]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	if (!line_element[start_index + 1])
		return (set_material_default(obj));
	else
	{
		if (set_material_common(obj, line_element, start_index) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
