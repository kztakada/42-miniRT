/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:10:02 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 16:10:14 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rgb_color_info(t_color color)
{
	printf("  Color: (%d, %d, %d)\n", (int)(256.0F * clamp_color(color.r, 0.0F,
				0.999F)), (int)(256.0F * clamp_color(color.g, 0.0F, 0.999F)),
		(int)(256.0F * clamp_color(color.b, 0.0F, 0.999F)));
}

void	print_rgb_color(t_color color)
{
	printf(" %d,%d,%d", (int)(256.0F * clamp_color(color.r, 0.0F, 0.999F)),
		(int)(256.0F * clamp_color(color.g, 0.0F, 0.999F)), (int)(256.0F
			* clamp_color(color.b, 0.0F, 0.999F)));
}
