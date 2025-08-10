/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:52:58 by katakada          #+#    #+#             */
/*   Updated: 2025/08/10 20:49:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	set_default_scene(t_scene *scene)
{
	set_default_scene_common(scene);
	srand(time(NULL));
	scene->sampling.max_count = MAX_RAND_SAMPLING;
	scene->is_bonus = TRUE;
}

int	main(int argc, char **argv)
{
	static t_scene	scene;

	printf(F_MSG);
	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd(ERR_INVALID_ARG, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	set_default_scene(&scene);
	if (create_scene(&scene, argv[1]) == FAILURE)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	setup_scene(&scene);
	if (render_scene_to_mlx(&scene) == FAILURE)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
