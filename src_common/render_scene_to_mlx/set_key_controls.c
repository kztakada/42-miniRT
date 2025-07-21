/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_key_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:04:02 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 17:51:57 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_down(int button, int mouse_x, int mouse_y, void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	(void)r_scene;
	if (button == MOUSE_LEFT)
	{
		printf("Mouse left button pressed at (%d, %d)\n", mouse_x, mouse_y);
		// Handle left mouse button down event
	}
	else if (button == MOUSE_RIGHT)
	{
		printf("Mouse right button pressed at (%d, %d)\n", mouse_x, mouse_y);
		// Handle right mouse button down event
	}
	return (0);
}

int	mouse_up(int button, int mouse_x, int mouse_y, void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	(void)r_scene;
	(void)mouse_x;
	(void)mouse_y;
	if (button == MOUSE_LEFT || button == MOUSE_MIDDLE || button == MOUSE_RIGHT)
	{
		printf("Mouse button released at (%d, %d)\n", mouse_x, mouse_y);
		// Handle mouse button up event
	}
	return (0);
}

int	close_window(void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	printf("Window closed\n");
	free_scene_with_mlx(r_scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int keycode, void *param)
{
	t_scene_with_mlx	*r_scene;

	r_scene = (t_scene_with_mlx *)param;
	if (keycode == KEY_ESC)
		close_window(r_scene);
	else if (keycode == KEY_LEFT)
	{
		printf("Left arrow key pressed\n");
		// Handle left arrow key event
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("Right arrow key pressed\n");
		// Handle right arrow key event
	}
	return (0);
}

void	set_key_controls(t_scene_with_mlx *r_scene)
{
	mlx_hook(r_scene->mlx_win, 17, 0, close_window, r_scene);
	mlx_hook(r_scene->mlx_win, 4, 1L << 2, mouse_down, r_scene);
	mlx_hook(r_scene->mlx_win, 5, 1L << 3, mouse_up, r_scene);
	mlx_key_hook(r_scene->mlx_win, key_press, r_scene);
}
