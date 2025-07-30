/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:33:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 19:52:13 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	format_check_sphere(char **line_element)
{
	if (element_count(line_element) != 4)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float(line_element[2]) == FAILURE
		|| is_number_float_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	return (SUCCESS);
}

t_binary_result	format_check_plane(char **line_element)
{
	if (element_count(line_element) != 4)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	return (SUCCESS);
}

t_binary_result	format_check_cylinder(char **line_element)
{
	if (element_count(line_element) != 6)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float(line_element[3]) == FAILURE
		|| is_number_float(line_element[4]) == FAILURE
		|| is_number_float_three_dimensional(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	return (SUCCESS);
}
