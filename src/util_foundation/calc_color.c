/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:55 by katakada          #+#    #+#             */
/*   Updated: 2025/07/31 13:55:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color	add_colors(t_color c1, t_color c2)
{
	t_color	added_color;

	added_color.r = c1.r + c2.r;
	added_color.g = c1.g + c2.g;
	added_color.b = c1.b + c2.b;
	return (added_color);
}

inline t_color	scale_color(float coefficient, t_color c1)
{
	t_color	scaled_color;

	scaled_color.r = c1.r * coefficient;
	scaled_color.g = c1.g * coefficient;
	scaled_color.b = c1.b * coefficient;
	return (scaled_color);
}

inline t_color	multiply_colors(t_color c1, t_color c2)
{
	t_color	multiplied_color;

	multiplied_color.r = c1.r * c2.r;
	multiplied_color.g = c1.g * c2.g;
	multiplied_color.b = c1.b * c2.b;
	return (multiplied_color);
}

inline float	clamp_color(float color_value, float limit_min, float limit_max)
{
	if (color_value < limit_min)
		return (limit_min);
	if (color_value > limit_max)
		return (limit_max);
	return (color_value);
}

int	color_to_int_rgb(t_color color)
{
	if (color.r != color.r)
		color.r = 0;
	if (color.g != color.g)
		color.g = 0;
	if (color.b != color.b)
		color.b = 0;
	if (color.b > 1.0F && color.b >= color.r && color.b >= color.g)
		color = scale_color(1.0F / color.b, color);
	if (color.g > 1.0F && color.g >= color.r && color.g >= color.b)
		color = scale_color(1.0F / color.g, color);
	if (color.r > 1.0F && color.r >= color.g && color.r >= color.b)
		color = scale_color(1.0F / color.r, color);
	// if (gamma_correction)
	// 	color = color_gamma_encode(color);
	return ((int)(256.0F * clamp_color(color.r, 0.0F,
				0.999F)) << 16 | (int)(256.0F * clamp_color(color.g, 0.0F,
				0.999F)) << 8 | (int)(256.0F * clamp_color(color.b, 0.0F,
				0.999F)) << 0);
}
