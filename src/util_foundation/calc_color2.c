/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:04 by katakada          #+#    #+#             */
/*   Updated: 2025/08/05 22:00:20 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color	mix_colors_by_ratio(t_color c1, t_color c2, float c1_ratio)
{
	t_color	result;
	float	inverse_ratio;

	if (c1_ratio < 0.0F || c1_ratio > 1.0F)
		return (put_out_error_color(ERR_INVALID_C_RATIO));
	inverse_ratio = 1.0F - c1_ratio;
	result.r = c1.r * c1_ratio + c2.r * inverse_ratio;
	result.g = c1.g * c1_ratio + c2.g * inverse_ratio;
	result.b = c1.b * c1_ratio + c2.b * inverse_ratio;
	return (result);
}

inline t_color	add_lighting(t_color base, t_color light, float intensity)
{
	t_color	result;

	intensity = clampf(intensity, 0.0F, 1.0F);
	result.r = base.r * light.r * intensity;
	result.g = base.g * light.g * intensity;
	result.b = base.b * light.b * intensity;
	result.r = clampf(result.r, 0.0F, 1.0F);
	result.g = clampf(result.g, 0.0F, 1.0F);
	result.b = clampf(result.b, 0.0F, 1.0F);
	return (result);
}

t_color	get_opposite_color(t_color color)
{
	t_color	opposite_color;

	opposite_color.r = 1.0F - color.r;
	opposite_color.g = 1.0F - color.g;
	opposite_color.b = 1.0F - color.b;
	return (opposite_color);
}
