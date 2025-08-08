/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rendering_console_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 23:22:27 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 01:20:12 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_rendering_progress(t_scene *scene)
{
	int	bar_width;
	int	filled;
	int	i;

	printf("\033[32mRendering Progress:\n");
	printf("  Samples: %d / %d\n", scene->sampling.count,
		scene->sampling.max_count);
	printf("  Progress: %.1f%%\n", (float)scene->sampling.count
		/ scene->sampling.max_count * 100.0f);
	bar_width = 30;
	filled = (scene->sampling.count * bar_width) / scene->sampling.max_count;
	printf("  [");
	i = 0;
	while (i < bar_width)
	{
		if (i++ < filled)
			printf("%c", '#');
		else
			printf("%c", '-');
	}
	printf("]\n\n");
	if (scene->sampling.count >= scene->sampling.max_count)
		printf("Status: COMPLETE!\033[0m\n");
	else
		printf("Status: Rendering...\033[0m\n");
}

static void	print_light_mode(t_scene_with_mlx *r_scene)
{
	t_light	*light;

	if (!r_scene || !r_scene->key.selected_light)
		return ;
	light = get_light(r_scene->key.selected_light);
	if (light)
	{
		printf("Selected Light:\n");
		printf("  Index: %d\n", r_scene->key.selected_light_index);
		printf("  Position: (%.2f, %.2f, %.2f)\n", light->pos.x, light->pos.y,
			light->pos.z);
		printf("  Brightness: %.2f\n", light->brightness);
		print_rgb_color_info(light->color);
	}
	else
	{
		printf("No light selected.\n");
	}
}

static void	print_key_status(t_scene_with_mlx *r_scene)
{
	t_key_control	*key;
	t_scene			*scene;

	scene = r_scene->scene;
	key = &r_scene->key;
	printf("\nSELECT MODE: ");
	if (key->mode == CAMERA_MODE)
	{
		printf("Camera Mode\n");
		printf("Pos: %f, %f, %f\n", scene->camera.pos.x, scene->camera.pos.y,
			scene->camera.pos.z);
		printf("Dir: %f, %f, %f\n", scene->camera.dir.x, scene->camera.dir.y,
			scene->camera.dir.z);
	}
	else if (key->mode == LIGHT_MODE)
		print_light_mode(r_scene);
	else
	{
		printf("Object Mode\n");
		if (key->selected_obj)
			key->selected_obj->print_focused_obj(key->selected_obj);
		else
			printf("No object selected\n");
	}
	printf("\n");
}

static void	print_minirt_header(void)
{
	printf("\033[32m========================================\n");
	printf("         miniRT Renderer\n");
	printf("========================================\n");
	printf("\033[0m");
}

void	print_rendering_console(t_scene_with_mlx *r_scene)
{
	t_scene		*scene;
	static int	completion_displayed = 0;

	scene = r_scene->scene;
	// 完了していて、既に表示済みなら何もしない
	if (scene->sampling.count >= scene->sampling.max_count
		&& r_scene->key.is_modified == FALSE && completion_displayed)
		return ;
	r_scene->key.is_modified = FALSE;
	printf("\033[2J\033[H"); // 画面をクリア
	print_minirt_header();
	print_rendering_progress(scene);
	print_key_status(r_scene);
	if (scene->sampling.count >= scene->sampling.max_count)
	{
		printf("Press ESC to exit or any key to continue...\n");
		completion_displayed = 1; // 完了表示フラグ
	}
	else
		completion_displayed = 0;
	print_scene_rt_format(r_scene, FALSE);
	fflush(stdout);
}
