/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_closest_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:45:42 by katakada          #+#    #+#             */
/*   Updated: 2025/07/30 14:53:04 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*calc_closest_obj(t_list *objs, t_ray *pov_ray, t_hit *hit)
{
	t_obj	*closest_obj;
	float	min_t;
	t_hit	collision;

	closest_obj = NULL;
	min_t = FLT_MAX;
	while (objs)
	{
		collision.is_hit = FALSE;
		collision.t = -1.0F;
		collision = get_obj(objs)->calc_obj_hit(get_obj(objs), pov_ray);
		collision.pov_dir = pov_ray->dir;
		if (collision.is_hit && collision.t > EPSILON && collision.t < min_t)
		{
			min_t = collision.t;
			closest_obj = get_obj(objs);
			if (hit != NULL)
				*hit = collision;
		}
		objs = objs->next;
	}
	return (closest_obj);
}
