/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:27:01 by katakada          #+#    #+#             */
/*   Updated: 2025/07/22 15:17:39 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	create_scene(t_scene *scene, const char *file_path)
{
	printf("Creating scene from file: %s\n", file_path);
	scene->screen.dots = malloc(sizeof(t_color) * scene->screen.width
			* scene->screen.height);
	if (scene->screen.dots == NULL)
		return (put_out_failure(ERR_MALLOC_FAIL));
	ft_bzero(scene->screen.dots, sizeof(t_color) * scene->screen.width
		* scene->screen.height);
	return (SUCCESS);
}
