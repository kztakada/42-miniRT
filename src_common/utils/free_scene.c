/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:40:14 by katakada          #+#    #+#             */
/*   Updated: 2025/07/16 21:41:50 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	// Free lights
	ft_lstclear(&scene->lights, free);
	// Free objects
	ft_lstclear(&scene->objs, free);
}
