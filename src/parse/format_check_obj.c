/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:30:32 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/03 18:16:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	format_check_sphere(char **line_element)
{
	int	num_element;

	num_element = element_count(line_element);
	if ((num_element != 4 && num_element != 6 && num_element != 7
			&& num_element != 9))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float(line_element[2]) == FAILURE
		|| is_number_float_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element == 4)
		return (SUCCESS);
	if (is_number_float_three_dimensional(line_element[4]) == FAILURE
		|| is_number_float(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element <= 6)
		return (SUCCESS);
	if (strcmp(line_element[6], "1") != 0 && strcmp(line_element[6], "0"))
		return (put_out_format_error(line_element[0], ERR_BOOL));
	return (SUCCESS);
}

t_binary_result	format_check_plane(char **line_element)
{
	int	num_element;

	num_element = element_count(line_element);
	if ((num_element != 4 && num_element != 6 && num_element != 7
			&& num_element != 9))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element == 4)
		return (SUCCESS);
	if (is_number_float_three_dimensional(line_element[4]) == FAILURE
		|| is_number_float(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element <= 6)
		return (SUCCESS);
	if (strcmp(line_element[6], "1") != 0 && strcmp(line_element[6], "0"))
		return (put_out_format_error(line_element[0], ERR_BOOL));
	return (SUCCESS);
}

t_binary_result	format_check_cylinder(char **line_element)
{
	int	num_element;

	num_element = element_count(line_element);
	if (num_element != 6 && num_element != 8 && num_element != 9
		&& num_element != 11)
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float(line_element[3]) == FAILURE
		|| is_number_float(line_element[4]) == FAILURE
		|| is_number_float_three_dimensional(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element == 6)
		return (SUCCESS);
	if (is_number_float_three_dimensional(line_element[6]) == FAILURE
		|| is_number_float(line_element[7]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element <= 8)
		return (SUCCESS);
	if ((strcmp(line_element[8], "1") != 0 && strcmp(line_element[8], "0")))
		return (put_out_format_error(line_element[0], ERR_BOOL));
	return (SUCCESS);
}

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
	if (num_element != 7 && num_element != 9 && num_element != 10
		&& num_element != 12)
		put_out_format_error(line_element[0], ERR_NUM_ARG);
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE
		|| is_number_float_three_dimensional(line_element[2]) == FAILURE
		|| is_number_float(line_element[3]) == FAILURE
		|| is_number_float(line_element[4]) == FAILURE
		|| is_number_float(line_element[5]) == FAILURE
		|| is_number_float_three_dimensional(line_element[6]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element == 7)
		return (SUCCESS);
	if (is_number_float_three_dimensional(line_element[7]) == FAILURE
		|| is_number_float(line_element[8]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NOT_NUMBER));
	if (num_element <= 9)
		return (SUCCESS);
	if (strcmp(line_element[9], "1") != 0 && strcmp(line_element[9], "0"))
		return (put_out_format_error(line_element[0], ERR_BOOL));
	return (SUCCESS);
}
