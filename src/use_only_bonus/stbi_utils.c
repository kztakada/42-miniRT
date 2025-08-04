/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stbi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:57:38 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/04 14:05:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_binary_result	stbi_data_to_color(unsigned char *img_data, int width,
		int height, t_texture *c_texture)
{
	int		i;
	size_t	pixel;

	c_texture->color = malloc(width * height * sizeof(t_color));
	if (c_texture->color == NULL)
		return (FAILURE);
	i = 0;
	while (i < width * height)
	{
		pixel = i * 3; // RGB = 3 bytes per pixel
		c_texture->color[i].r = img_data[pixel] / 255.0F;
		c_texture->color[i].g = img_data[pixel + 1] / 255.0F;
		c_texture->color[i].b = img_data[pixel + 2] / 255.0F;
		i++;
	}
	return (SUCCESS);
}
