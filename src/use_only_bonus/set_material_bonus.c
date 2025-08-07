/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:32:31 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/07 14:59:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "stb_image.h"

static t_binary_result	is_file_exist(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	else
	{
		close(fd);
		return (SUCCESS);
	}
}

static t_binary_result	set_texture(t_texture *texture, char *type,
		char *file_path)
{
	unsigned char	*img_data;
	int				width;
	int				height;

	if (is_file_exist(file_path) == FAILURE)
		return (put_out_format_error(type, ERR_NO_FILE));
	img_data = stbi_load(file_path, &width, &height, NULL, 3);
	if (!img_data)
		return (FAILURE);
	texture->width = width;
	texture->height = height;
	texture->file_path = ft_strdup(file_path);
	if (!texture->file_path)
	{
		free(img_data);
		return (put_out_format_error(type, ERR_MALLOC_FAIL));
	}
	if (stbi_data_to_color(img_data, width, height, texture) == FAILURE)
	{
		free(img_data);
		return (put_out_format_error(type, ERR_MALLOC_FAIL));
	}
	free(img_data);
	return (SUCCESS);
}

static void	set_has_flag(t_obj *obj, char **line_element, int index)
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
	else
	{
		if (set_material_common(obj, line_element, start_index) == FAILURE)
			return (FAILURE);
	}
	set_has_flag(obj, line_element, start_index + 3);
	if (obj->material.has_texture == TRUE)
		if (set_texture(&(obj->material.texture), line_element[0],
				line_element[start_index + 4]) == FAILURE)
			return (FAILURE);
	if (obj->material.has_bump == TRUE)
	{
		if (set_texture(&(obj->material.bump), line_element[0],
				line_element[start_index + 5]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
