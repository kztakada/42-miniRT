/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:53:18 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 18:56:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_24bit_color(t_color *color)
{
	if (!color)
		return (0);
	return (((int)(color->r * 255) << 16) | ((int)(color->g
				* 255) << 8) | (int)(color->b * 255));
}

static t_color	get_rgb_color(int color)
{
	t_color	rgb_color;

	rgb_color.r = ((color >> 16) & 0xFF) / 255.0F;
	rgb_color.g = ((color >> 8) & 0xFF) / 255.0F;
	rgb_color.b = (color & 0xFF) / 255.0F;
	return (rgb_color);
}

void	color_up(t_color *color)
{
	int	color_24bit;

	if (!color)
		return ;
	color_24bit = get_24bit_color(color);
	color_24bit += BRIGHTNESS_STEP;
	if (color_24bit > 0xFFFFFF)
		color_24bit = 0;
	if (color_24bit < 0x000000)
		color_24bit = 0xFFFFFF;
	*color = get_rgb_color(color_24bit);
}

void	color_down(t_color *color)
{
	int	color_24bit;

	if (!color)
		return ;
	color_24bit = get_24bit_color(color);
	color_24bit -= BRIGHTNESS_STEP;
	if (color_24bit > 0xFFFFFF)
		color_24bit = 0xFFFFFF;
	if (color_24bit < 0x000000)
		color_24bit = 0;
	*color = get_rgb_color(color_24bit);
}
