/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_objs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:44:00 by katakada          #+#    #+#             */
/*   Updated: 2025/08/09 15:44:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_binary_result	check_format_bonus(char **line_element, char *type)
{
	if (is_positive_float_three_dimensional(line_element[0]) == FAILURE)
		return (put_out_format_error(type, ERR_SPECULAR_ARG));
	if (is_positive_float(line_element[1]) == FAILURE)
		return (put_out_format_error(type, ERR_REFRACT_ARG));
	if (line_element[2] == NULL)
		return (SUCCESS);
	if (strcmp(line_element[2], "1") == 0)
		return (SUCCESS);
	if (strcmp(line_element[2], "0") == 0)
		return (SUCCESS);
	return (put_out_format_error(type, ERR_CHECKER_ARG));
}

t_binary_result	format_check_sphere(char **line_element, t_bool is_bonus)
{
	int	num_element;

	num_element = element_count(line_element);
	if (!is_valid_num_of_element(num_element, 4, is_bonus))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_positive_float(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_DIAMETER_ARG));
	if (is_positive_int_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	if (num_element == 4)
		return (SUCCESS);
	if (check_format_bonus(line_element + 4, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	format_check_plane(char **line_element, t_bool is_bonus)
{
	int	num_element;

	num_element = element_count(line_element);
	if (!is_valid_num_of_element(num_element, 4, is_bonus))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	if (is_positive_int_three_dimensional(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	if (num_element == 4)
		return (SUCCESS);
	if (check_format_bonus(line_element + 4, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	format_check_cylinder(char **line_element, t_bool is_bonus)
{
	int	num_element;

	num_element = element_count(line_element);
	if (!is_valid_num_of_element(num_element, 6, is_bonus))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	if (is_positive_float(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_DIAMETER_ARG));
	if (is_positive_float(line_element[4]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_HEIGHT_ARG));
	if (is_positive_int_three_dimensional(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	if (num_element == 6)
		return (SUCCESS);
	if (check_format_bonus(line_element + 6, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	format_check_cone(char **line_element, t_bool is_bonus)
{
	int	num_element;

	num_element = element_count(line_element);
	if (!is_valid_num_of_element(num_element, 7, is_bonus))
		return (put_out_format_error(line_element[0], ERR_NUM_ARG));
	if (is_number_float_three_dimensional(line_element[1]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_POS_ARG));
	if (is_number_float_three_dimensional(line_element[2]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_NORMAL_ARG));
	if (is_positive_float(line_element[3]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_HEIGHT_ARG));
	if (is_positive_float(line_element[4]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_HEIGHT_ARG));
	if (is_number_float(line_element[5]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_ANGLE_ARG));
	if (is_positive_int_three_dimensional(line_element[6]) == FAILURE)
		return (put_out_format_error(line_element[0], ERR_COLOR_ARG));
	if (num_element == 7)
		return (SUCCESS);
	if (check_format_bonus(line_element + 7, line_element[0]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
