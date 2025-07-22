/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:02:15 by katakada          #+#    #+#             */
/*   Updated: 2025/07/21 22:12:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	raytracing(t_scene *scene, t_ray *render_ray, int max_depth)
{
	t_color color;

	(void)scene;
	(void)render_ray;
	if (max_depth <= 0)
		return ((t_color){0.0f, 0.0f, 0.0f});
	color = (t_color){255.0f, 255.0f, 255.0f};
	return (color);
}