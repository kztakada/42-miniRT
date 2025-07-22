/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:13:17 by katakada          #+#    #+#             */
/*   Updated: 2025/07/22 21:23:22 by katakada         ###   ########.fr       */
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
