/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:03:02 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 20:18:54 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	set_material(t_obj *obj, char **line_element, int start_index)
{
	if (set_color(&(obj->material.color), line_element[start_index]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
