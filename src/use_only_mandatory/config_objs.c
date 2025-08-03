/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_objs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:16:32 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/03 23:16:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/minirt_mandatory.h"

t_binary_result	config_objs(t_scene *scene, char **line_element)
{
	int		result_status;
	t_obj	*obj;
	t_list	*new;

	obj = malloc(sizeof(t_obj) * 1);
	if (!obj)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL));
	if (ft_strcmp(line_element[0], "sp") == 0)
		result_status = config_sphere(line_element, obj);
	else if (ft_strcmp(line_element[0], "pl") == 0)
		result_status = config_plane(line_element, obj);
	else if (ft_strcmp(line_element[0], "cy") == 0)
		result_status = config_cylinder(line_element, obj);
	else
		return (put_out_format_error(line_element[0], ERR_NO_IDENT), free(obj),
			FAILURE);
	new = ft_lstnew(obj);
	if (!new)
		put_out_format_error(line_element[0], ERR_MALLOC_FAIL);
	ft_lstadd_back(&(scene->objs), new);
	return (result_status);
}
