/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:13:17 by katakada          #+#    #+#             */
/*   Updated: 2025/07/24 18:35:39 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline float	vector_len(t_vector v)
{
	t_vector	squared_v;
	float		length_from_origin_coordinate;

	squared_v.x = v.x * v.x;
	squared_v.y = v.y * v.y;
	squared_v.z = v.z * v.z;
	length_from_origin_coordinate = sqrtf(squared_v.x + squared_v.y
			+ squared_v.z);
	return (length_from_origin_coordinate);
}

inline t_vector	get_ray_pos_at_t(t_ray ray, float t)
{
	t_vector	pos;

	pos.x = ray.pos.x + ray.dir.x * t;
	pos.y = ray.pos.y + ray.dir.y * t;
	pos.z = ray.pos.z + ray.dir.z * t;
	return (pos);
}

inline float	calc_distance(t_vector a, t_vector b)
{
	t_vector	diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	return (vector_len(diff));
}

// dot product is also called inner product
inline float	vectors_dot(t_vector a, t_vector b)
{
	float	inner_product;

	inner_product = a.x * b.x + a.y * b.y + a.z * b.z;
	return (inner_product);
}

inline t_vector	inverse_vector(t_vector v)
{
	t_vector	inverse_v;

	inverse_v.x = -v.x;
	inverse_v.y = -v.y;
	inverse_v.z = -v.z;
	return (inverse_v);
}
