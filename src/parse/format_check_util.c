/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:17:38 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/29 21:49:20 by kharuya          ###   ########.fr       */
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

t_binary_result	is_number_float(char *element)
{
	int		i;
	t_bool	decimal_point_flag;

	i = 0;
	decimal_point_flag = FALSE;
	if (element[i] == '+'|| element[i] == '-')
		i++;
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

t_binary_result	is_number_float_three_dimensional(char *element)
{
	char	**split;
	int		i;

	split = ft_split(element, ',');
	i = 0;
	while (split[i])
	{
		if (is_number_float(split[i]) == FAILURE)
		{
			ft_free_char2(split);
			return (FAILURE);
		}
		i++;
	}
	ft_free_char2(split);
	return (SUCCESS);
}

int	element_count(char **line_element)
{
	int i;

	i = 0;
	while (line_element[i] != NULL)
		i++;
	return (i);
}
