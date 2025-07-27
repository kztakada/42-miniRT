/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_key_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:04:02 by katakada          #+#    #+#             */
/*   Updated: 2025/07/27 19:55:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mouse_down(int button, int mouse_x, int mouse_y, void *param)
{
	t_scene_with_mlx	*r_scene;
	t_vector			dot_pos;
	t_raytracing		rt;

	if (button != MOUSE_LEFT)
		return (0);
	r_scene = (t_scene_with_mlx *)param;
	dot_pos = convert_xy_pos_to_xyz_vector((float)mouse_x, (float)mouse_y,
			r_scene->scene);
	rt.pov_ray.pos = r_scene->scene->camera.pos;
	rt.pov_ray.dir = normalize_vector(sub_vectors(dot_pos, rt.pov_ray.pos));
	rt.closest_obj = calc_closest_obj(r_scene->scene->objs, &rt.pov_ray,
			&rt.hit);
	if (rt.closest_obj == NULL)
		return (0);
	r_scene->key.selected_obj = rt.closest_obj;
	r_scene->key.mode = OBJECT_MODE;
	return (0);
}

static int	close_window(void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	if (!r_scene)
		return (0);
	printf("Window closed\n");
	free_scene_with_mlx(r_scene);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	toggle_selected_mode(t_scene_with_mlx *r_scene)
{
	if (r_scene->key.mode == CAMERA_MODE)
		r_scene->key.mode = LIGHT_MODE;
	else if (r_scene->key.mode == LIGHT_MODE)
		r_scene->key.mode = OBJECT_MODE;
	else
		r_scene->key.mode = CAMERA_MODE;
}

static int	key_press(int keycode, void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_UP
		|| keycode == KEY_DOWN)
		press_arrow_key(r_scene, keycode);
	else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E)
		press_move_key(r_scene, keycode);
	else if (keycode == KEY_PLUS)
		select_next_light(r_scene);
	else if (keycode == KEY_MINUS)
		select_prev_light(r_scene);
	else if (keycode == KEY_SPACE)
		toggle_selected_mode(r_scene);
	else if (keycode == KEY_C)
		reset_scene_all(r_scene);
	else if (keycode == KEY_R)
		reset_selected_mode_target(r_scene);
	else if (keycode == KEY_ESC)
		close_window(r_scene);
	return (0);
}

void	set_key_controls(t_scene_with_mlx *r_scene)
{
	mlx_hook(r_scene->mlx_win, 17, 0, close_window, r_scene);
	mlx_hook(r_scene->mlx_win, 4, 1L << 2, mouse_down, r_scene);
	// mlx_hook(r_scene->mlx_win, 5, 1L << 3, mouse_up, r_scene);
	mlx_key_hook(r_scene->mlx_win, key_press, r_scene);
}
