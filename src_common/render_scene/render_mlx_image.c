/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mlx_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:46:12 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 17:57:42 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_mlx_image(t_scene_with_mlx *r_scene)
{
	t_scene	*scene;

	scene = r_scene->scene;
	if (scene->sampling.count == scene->sampling.max_count)
		return ;
	return ;
}
