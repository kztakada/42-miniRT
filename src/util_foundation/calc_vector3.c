/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:25:17 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 12:41:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	calc_reflection_vector(t_vector incident, t_vector normal)
{
	t_vector	reflect_vector;
	float		dot_product;

	dot_product = vectors_dot(incident, normal);
	reflect_vector = sub_vectors(incident, scale_vector(2.0F * dot_product,
				normal));
	return (reflect_vector);
}

// Rodrigues rotation formula
t_vector	calc_rodrigues_rotation(t_vector current_dir,
		t_vector rotation_axis, float angle)
{
	t_vector	rotated_dir;
	float		cos_angle;
	float		sin_angle;
	float		dot_product;
	t_vector	cross_product;

	cos_angle = cosf(angle * (float)M_PI / 180.0F);
	sin_angle = sinf(angle * (float)M_PI / 180.0F);
	dot_product = vectors_dot(current_dir, rotation_axis);
	cross_product = cross_vector(rotation_axis, current_dir);
	rotated_dir.x = current_dir.x * cos_angle + cross_product.x * sin_angle
		+ rotation_axis.x * dot_product * (1.0F - cos_angle);
	rotated_dir.y = current_dir.y * cos_angle + cross_product.y * sin_angle
		+ rotation_axis.y * dot_product * (1.0F - cos_angle);
	rotated_dir.z = current_dir.z * cos_angle + cross_product.z * sin_angle
		+ rotation_axis.z * dot_product * (1.0F - cos_angle);
	return (normalize_vector(rotated_dir));
}
