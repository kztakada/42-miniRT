/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_util2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:43:25 by katakada          #+#    #+#             */
/*   Updated: 2025/08/08 21:46:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_binary_result	is_number_int(char *element)
{
	int	i;

	i = 0;
	if (element[i] == '+' || element[i] == '-')
		i++;
	while (element[i])
	{
		if (element[i] < '0' || element[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_binary_result	is_positive_int(char *element)
{
	int	i;

	i = 0;
	if (element[i] == '+')
		i++;
	while (element[i])
	{
		if (element[i] < '0' || element[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_binary_result	is_positive_float(char *element)
{
	int		i;
	t_bool	decimal_point_flag;

	i = 0;
	decimal_point_flag = FALSE;
	if (element[i] == '+')
		i++;
	if (element[i] == '.')
		return (FAILURE);
	while (element[i])
	{
		if (element[i] == '.' && decimal_point_flag == FALSE)
			decimal_point_flag = TRUE;
		else if (element[i] == '.' && decimal_point_flag == TRUE)
			return (FAILURE);
		else if (element[i] < '0' || element[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_binary_result	is_number_float(char *element)
{
	int		i;
	t_bool	decimal_point_flag;

	i = 0;
	decimal_point_flag = FALSE;
	if (element[i] == '+' || element[i] == '-')
		i++;
	if (element[i] == '.')
		return (FAILURE);
	while (element[i])
	{
		if (element[i] == '.' && decimal_point_flag == FALSE)
			decimal_point_flag = TRUE;
		else if (element[i] == '.' && decimal_point_flag == TRUE)
			return (FAILURE);
		else if (element[i] < '0' || element[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

t_bool	is_valid_num_of_element(int num_element, int required, t_bool is_bonus)
{
	if (is_bonus)
	{
		if (num_element == required || (num_element >= required + 2
				&& num_element <= required + 5))
			return (TRUE);
	}
	else
	{
		if (num_element == required)
			return (TRUE);
	}
	return (FALSE);
}
