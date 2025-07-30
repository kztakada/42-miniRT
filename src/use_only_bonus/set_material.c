/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:02:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/30 15:30:56 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "stb_image.h"

static t_binary_result	set_texture(t_texture *texture, char *type, char *file_path)
{
	unsigned char	*img_data;
	int				width;
	int				height;

	// ここにファイルのexist_checkを入れる
	img_data = stbi_load(file_path, &width, &height, NULL, 3);
	if (!img_data)
		return (FAILURE);
	texture->width = width;
	texture->height = height;
	if (stbi_data_to_color(img_data, width, height, texture) == -1)
	{
		free(img_data);
		return (put_out_format_error(type, ERR_MALLOC_FAIL));
	}
	free(img_data);
	return (SUCCESS);
}

static void	set_has_flag(t_obj *obj, char **line_element,
	int index)
{
	if (line_element[index])
	{
		obj->material.is_checkerboard = TRUE;
		if (line_element[index + 1])
		{
			obj->material.has_texture = TRUE;
			if (line_element[index + 2])
				obj->material.has_bump = TRUE;
			else
				obj->material.has_bump = FALSE;
		}
		else
		{
			obj->material.has_texture = FALSE;
			obj->material.has_bump = FALSE;
		}
	}
	else
	{
		obj->material.is_checkerboard = FALSE;
		obj->material.has_texture = FALSE;
		obj->material.has_bump = FALSE;
	}
}

t_binary_result	set_material(t_obj *obj, char **line_element, int start_index)
{
	if (set_color(&(obj->material.color), line_element[start_index]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	if (!line_element[start_index + 1])
		return (set_material_default(obj));
	else if (set_spec_mirror(obj, line_element[start_index + 1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	obj->material.refract = ft_atof(line_element[start_index + 2]);
	if (obj->material.refract < 0.0f)
		return (put_out_format_error(line_element[0], ERR_INVALID_VALUE));
	set_has_flag(obj, line_element, start_index + 3);
	if (obj->material.has_texture == TRUE)
		return (set_texture(&(obj->material.texture), line_element[0],
			line_element[start_index + 4]));
	if (obj->material.has_bump == TRUE)
	{
		return (set_texture(&(obj->material.bump), line_element[0],
			line_element[start_index + 5]));
	}
	return (SUCCESS);
}
