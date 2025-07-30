/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stbi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:57:38 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/28 07:59:05 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	stbi_data_to_color(unsigned char *img_data, int width, int height,
		t_texture *c_texture)
{
	int		i;
	size_t	pixel;

	c_texture->color = malloc(width * height * sizeof(t_color));
	if (c_texture->color == NULL)
		return (-1);
	i = 0;
	while (i < width * height)
	{
		pixel = i * 3; // RGB = 3 bytes per pixel
		c_texture->color[i].r = img_data[pixel] / 255.0;
		c_texture->color[i].g = img_data[pixel + 1] / 255.0;
		c_texture->color[i].b = img_data[pixel + 2] / 255.0;
		i++;
	}
	return (0);
}
