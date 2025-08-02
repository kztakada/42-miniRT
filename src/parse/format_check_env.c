/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:23:56 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/01 04:58:47 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_binary_result	format_check_ambient(char **line_element, t_parse *format_info)
{
	if (format_info->ambient == TRUE)
		return (put_out_format_error(line_element[0], ERR_TYPE_IDENT));
	if (element_count(line_element) != 3)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
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
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_int(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	format_info->camera = TRUE;
	return (SUCCESS);
}

t_binary_result	format_check_light(char **line_element, t_parse *format_info)
{
	int	num_element;

	if ((format_info->large_light == TRUE && !ft_strcmp(line_element[0], "l"))
		|| (format_info->light_count != 0 && !ft_strcmp(line_element[0], "L")))
		return (put_out_format_error(line_element[0], ERR_L_TYPE_MIXED));
	if (format_info->large_light == TRUE)
		return (put_out_format_error(line_element[0], ERR_TYPE_IDENT));
	num_element = element_count(line_element);
	if (num_element != 4 && num_element != 3)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_float(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (line_element[3])
	{
		if (is_number_float_three_dimensional(line_element[3]) == FAILURE)
			return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	}
	if (!ft_strcmp(line_element[0], "l"))
		format_info->light_count++;
	if (!ft_strcmp(line_element[0], "L"))
		format_info->large_light = TRUE;
	return (SUCCESS);
}
