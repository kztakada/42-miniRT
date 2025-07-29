/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:23:56 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 21:11:40 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/minirt_bonus.h"

t_binary_result	format_check_ambient(char **line_element)
{
	if (element_count(line_element) != 3)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	return (SUCCESS);
}

t_binary_result	format_check_camera(char **line_element)
{
	if (element_count(line_element) != 4)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (is_number_int(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	return (SUCCESS);
}

t_binary_result	format_check_light(char **line_element)
{
	int	num_element;

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
	return (SUCCESS);
}
