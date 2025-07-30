/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ft_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:21:04 by katakada          #+#    #+#             */
/*   Updated: 2025/07/23 21:21:09 by katakada         ###   ########.fr       */
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
