/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_utils_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:54:39 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 23:56:57 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	toggle_selected_mode(t_scene_with_mlx *r_scene)
{
	if (r_scene->key.mode == CAMERA_MODE)
		r_scene->key.mode = LIGHT_MODE;
	else if (r_scene->key.mode == LIGHT_MODE)
		r_scene->key.mode = OBJECT_MODE;
	else
		r_scene->key.mode = CAMERA_MODE;
	r_scene->key.is_modified = TRUE;
	print_console(r_scene);
}

void	press_utils_key(t_scene_with_mlx *r_scene, int keycode)
{
	if (keycode == KEY_SPACE)
		toggle_selected_mode(r_scene);
	else if (keycode == KEY_C)
		reset_scene_all(r_scene);
	else if (keycode == KEY_R)
		reset_selected_mode_target(r_scene);
	else if (keycode == KEY_Z)
		toggle_console(r_scene);
}
