/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_arrow_key4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:53:18 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 00:08:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_up(t_color *color)
{
	int	color_24bit;

	if (!color)
		return ;
	color_24bit = get_24bit_color(color);
	color_24bit += LIGHT_COLOR_STEP;
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
	color_24bit -= LIGHT_COLOR_STEP;
	if (color_24bit > 0xFFFFFF)
		color_24bit = 0xFFFFFF;
	if (color_24bit < 0x000000)
		color_24bit = 0;
	*color = get_rgb_color(color_24bit);
}

void	grighten_up(float *brightness)
{
	if (!brightness)
		return ;
	*brightness += BRIGHTNESS_STEP;
	if (*brightness > 1.0F)
		*brightness = 1.0F;
	if (*brightness < 0.0F)
		*brightness = 0.0F;
}

void	grighten_down(float *brightness)
{
	if (!brightness)
		return ;
	*brightness -= BRIGHTNESS_STEP;
	if (*brightness > 1.0F)
		*brightness = 1.0F;
	if (*brightness < 0.0F)
		*brightness = 0.0F;
}
