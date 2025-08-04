/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_obj_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 06:06:28 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/04 06:06:59 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_binary_result	format_check_triangle(char **line_element)
{
	(void)line_element;
	return (SUCCESS);
}

t_binary_result	format_check_torus(char **line_element)
{
	(void)line_element;
	return (SUCCESS);
}


t_binary_result	format_check_cone(char **line_element)
{
	int	num_element;

	num_element = element_count(line_element);
	if (num_element != 7 && num_element != 9 && num_element != 12)
		put_out_format_error(line_element[0], ERR_NUM_ARG);
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float(line_element[3]) == FAILURE
		|| is_number_float(line_element[4]) == FAILURE
		|| is_number_float(line_element[5]) == FAILURE
		|| is_number_float_three_dimensional(line_element[6]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element == 9 || num_element == 12)
	{
		if (is_number_float_three_dimensional(line_element[7]) == FAILURE
			|| is_number_float(line_element[8]) == FAILURE)
			return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
		if (num_element == 12)
		{
			if (strcmp(line_element[9], "1") != 0 && strcmp(line_element[9], "0"))
				return (put_out_format_error(line_element[0], ERR_BOOL));
		}
	}
	return (SUCCESS);
}
