/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:25:17 by katakada          #+#    #+#             */
/*   Updated: 2025/07/25 00:17:46 by katakada         ###   ########.fr       */
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
