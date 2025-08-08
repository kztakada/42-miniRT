/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:36:28 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 20:41:58 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	parse_common_obj(char **line_element, t_obj *obj,
		t_bool is_bonus)
{
	if (ft_strcmp(line_element[0], "sp") == 0)
		return (parse_obj_sphere(line_element, obj, is_bonus));
	else if (ft_strcmp(line_element[0], "pl") == 0)
		return (parse_obj_plane(line_element, obj, is_bonus));
	else if (ft_strcmp(line_element[0], "cy") == 0)
		return (parse_obj_cylinder(line_element, obj, is_bonus));
	else
		return (SUCCESS);
}

static t_binary_result	parse_bonus_obj(char **line_element, t_obj *obj,
		t_bool is_bonus)
{
	if (obj->get_pos != NULL)
		return (SUCCESS);
	if (ft_strcmp(line_element[0], "co") == 0)
		return (parse_obj_cone(line_element, obj, is_bonus));
	else
		return (SUCCESS);
}

t_binary_result	parse_obj(t_scene *scene, char **line_element)
{
	t_obj	*obj;
	t_list	*new;

	obj = malloc(sizeof(t_obj) * 1);
	if (!obj)
		return (put_out_format_error(line_element[0], ERR_MALLOC_FAIL));
	ft_bzero(obj, sizeof(t_obj));
	if (parse_common_obj(line_element, obj, scene->is_bonus) == FAILURE)
		return (free(obj), FAILURE);
	if (scene->is_bonus == TRUE && obj->get_pos == NULL)
	{
		if (parse_bonus_obj(line_element, obj, scene->is_bonus) == FAILURE)
			return (free(obj), FAILURE);
	}
	if (obj->get_pos == NULL)
		return (free(obj), put_out_format_error(line_element[0], ERR_NO_IDENT));
	new = ft_lstnew(obj);
	if (!new)
		return (free(obj), put_out_format_error(line_element[0],
				ERR_MALLOC_FAIL));
	ft_lstadd_back(&(scene->objs), new);
	return (SUCCESS);
}
