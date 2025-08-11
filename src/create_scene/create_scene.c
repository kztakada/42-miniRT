/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:27:01 by katakada          #+#    #+#             */
/*   Updated: 2025/08/11 13:34:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_init(t_parse *format_info)
{
	format_info->ambient = FALSE;
	format_info->camera = FALSE;
	format_info->large_light = FALSE;
	format_info->light_count = 0;
}

static void	flush_get_next_line(int fd)
{
	char	*line;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

static t_binary_result	parse_scene(t_scene *scene, const char *file_path)
{
	int		rt_fd;
	char	*line;
	t_parse	format_info;

	parse_init(&format_info);
	rt_fd = open(file_path, O_RDONLY);
	if (rt_fd < 0)
		return (put_out_failure(ERR_NO_RT));
	while (TRUE)
	{
		line = get_next_line(rt_fd);
		if (!line)
			break ;
		if (parse_one_line_on_scene(scene, line, &format_info) == FAILURE)
		{
			free(line);
			flush_get_next_line(rt_fd);
			close(rt_fd);
			return (FAILURE);
		}
		free(line);
	}
	close(rt_fd);
	return (SUCCESS);
}

t_binary_result	create_scene(t_scene *scene, const char *file_path)
{
	scene->screen.dots = malloc(sizeof(t_color) * scene->screen.width
			* scene->screen.height);
	if (scene->screen.dots == NULL)
		return (put_out_failure(ERR_MALLOC_FAIL));
	ft_bzero(scene->screen.dots, sizeof(t_color) * scene->screen.width
		* scene->screen.height);
	if (parse_scene(scene, file_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
