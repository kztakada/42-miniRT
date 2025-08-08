/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:23:56 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/08 22:51:26 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_binary_result	format_check_ambient(char **line_element, t_parse *format_info)
{
	if (format_info->ambient == TRUE)
		return (put_out_format_error(line_element[0], ERR_TYPE_IDENT));
	if (element_count(line_element) != 3)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_positive_float(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_BRIGHT_ARG));
	if (is_positive_int_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	format_info->ambient = TRUE;
	return (SUCCESS);
}

t_binary_result	format_check_camera(char **line_element, t_parse *format_info)
{
	if (format_info->camera == TRUE)
		return (put_out_format_error(line_element[0], ERR_TYPE_IDENT));
	if (element_count(line_element) != 4)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	if (is_positive_int(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_FOV_ARG));
	format_info->camera = TRUE;
	return (SUCCESS);
}

static t_binary_result	format_check_light_common(char **line_element)
{
	int	num_element;

	num_element = element_count(line_element);
	if (num_element != 4 && num_element != 3)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_positive_float(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_BRIGHT_ARG));
	if (line_element[3])
	{
		if (is_positive_int_three_dimensional(line_element[3]) == FAILURE)
			return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	}
	return (SUCCESS);
}

t_binary_result	format_check_light(char **line_element, t_parse *format_info)
{
	if (format_info->large_light == TRUE)
		return (put_out_format_error(line_element[0], ERR_TYPE_IDENT));
	if (format_check_light_common(line_element) == FAILURE)
		return (FAILURE);
	format_info->large_light = TRUE;
	return (SUCCESS);
}

t_binary_result	format_check_lights_bonus(char **line_element,
		t_parse *format_info)
{
	if (format_check_light_common(line_element) == FAILURE)
		return (FAILURE);
	format_info->light_count++;
	return (SUCCESS);
}
