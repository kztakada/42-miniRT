/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:25:17 by katakada          #+#    #+#             */
/*   Updated: 2025/08/07 01:18:29 by katakada         ###   ########.fr       */
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

t_vector	calc_refraction_vector(t_vector incident, t_vector normal,
		float from_ior, float to_ior)
{
	float		eta;
	float		cos_i;
	float		k;
	float		cos_t;
	t_vector	refracted;

	eta = from_ior / to_ior;
	cos_i = -vectors_dot(incident, normal);
	// スネルの法則の判別式
	k = 1.0f - eta * eta * (1.0f - cos_i * cos_i);
	if (k < 0.0f)
		return ((t_vector){0.0f, 0.0f, 0.0f}); // 全反射
	cos_t = sqrtf(k);
	// 屈折ベクトルの計算
	refracted = add_vectors(scale_vector(eta, incident), scale_vector(eta
				* cos_i - cos_t, normal));
	return (refracted);
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
