/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_one_line_on_scene.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:02:57 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 22:20:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	is_comment_out(char *line)
{
	if (line[0] == '#')
		return (TRUE);
	return (FALSE);
}

static t_binary_result	parse_line_element(char **line_element, t_scene *scene,
		t_parse *format_info)
{
	if (ft_strcmp(line_element[0], "A") == 0)
		return (parse_ambient(scene, line_element, format_info));
	else if (ft_strcmp(line_element[0], "C") == 0)
		return (parse_camera(scene, line_element, format_info));
	else if (ft_strcmp(line_element[0], "L") == 0)
		return (parse_light(scene, line_element, format_info, FALSE));
	else if (scene->is_bonus == TRUE && ft_strcmp(line_element[0], "lt") == 0)
		return (parse_light(scene, line_element, format_info, TRUE));
	else
		return (parse_obj(scene, line_element));
}

t_binary_result	parse_one_line_on_scene(t_scene *scene, char *line,
		t_parse *format_info)
{
	char			**line_element;
	t_binary_result	result;

	line_element = ft_split_with_blank(line);
	if (!line_element)
		return (put_out_failure(ERR_MALLOC_FAIL));
	if (!line_element[0])
		return (ft_free_char2(line_element), SUCCESS);
	if (is_comment_out(line_element[0]))
		return (ft_free_char2(line_element), SUCCESS);
	result = parse_line_element(line_element, scene, format_info);
	ft_free_char2(line_element);
	return (result);
}
