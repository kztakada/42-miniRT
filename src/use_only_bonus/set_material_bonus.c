/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_material_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:32:31 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/09 00:31:18 by katakada         ###   ########.fr       */
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

static t_binary_result	load_png_to_texture(t_texture *texture, char *type,
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

static t_binary_result	set_textures(t_obj *obj, char **line_element,
		char *type)
{
	if (line_element[4] != NULL)
	{
		if (ft_strcmp(line_element[4], "NULL") != 0)
		{
			if (load_png_to_texture(&(obj->material.texture), type,
					line_element[4]) == FAILURE)
				return (FAILURE);
			obj->material.has_texture = TRUE;
		}
	}
	else
		return (SUCCESS);
	if (line_element[5] != NULL)
	{
		if (ft_strcmp(line_element[5], "NULL") != 0)
		{
			if (load_png_to_texture(&(obj->material.bump), type,
					line_element[5]) == FAILURE)
				return (FAILURE);
			obj->material.has_bump = TRUE;
		}
	}
	else
		return (SUCCESS);
	return (SUCCESS);
}

t_binary_result	set_material(t_obj *obj, char **line_element, char *type)
{
	if (set_material_common(obj, line_element, type) == FAILURE)
		return (FAILURE);
	if (line_element[3] != NULL)
	{
		if (ft_strcmp(line_element[3], "1") == 0)
			obj->material.is_checkerboard = TRUE;
	}
	else
		return (SUCCESS);
	if (set_textures(obj, line_element, type) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
