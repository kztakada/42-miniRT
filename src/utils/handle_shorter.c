/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shorter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:57:32 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 18:57:33 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_obj	*get_obj(t_list *obj)
{
	return ((t_obj *)obj->content);
}

inline t_light	*get_light(t_list *light)
{
	return ((t_light *)light->content);
}

t_bool	is_normal_range(t_vector normal)
{
	if (normal.x < -1.0f || normal.x > 1.0f || normal.y < -1.0f
		|| normal.y > 1.0f || normal.z < -1.0f || normal.z > 1.0f)
		return (FALSE);
	return (TRUE);
}
