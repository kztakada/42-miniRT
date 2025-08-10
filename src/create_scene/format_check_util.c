/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:17:38 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/10 20:40:21 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	element_count(char **line_element)
{
	int	i;

	i = 0;
	while (line_element[i] != NULL)
		i++;
	return (i);
}

static t_bool	has_2_commas(char *element)
{
	int	commas;
	int	i;

	commas = 0;
	i = 0;
	while (element[i])
	{
		if (element[i] == ',')
			commas++;
		i++;
	}
	return (commas == 2);
}

t_binary_result	is_number_float_three_dimensional(char *element)
{
	char	**split;
	int		i;

	if (has_2_commas(element) == FALSE)
		return (FAILURE);
	split = ft_split(element, ',');
	i = 0;
	while (split[i])
	{
		if (is_number_float(split[i]) == FAILURE)
			return (ft_free_char2(split), FAILURE);
		i++;
	}
	ft_free_char2(split);
	if (i != 3)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	is_positive_float_three_dimensional(char *element)
{
	char	**split;
	int		i;

	if (has_2_commas(element) == FALSE)
		return (FAILURE);
	split = ft_split(element, ',');
	i = 0;
	while (split[i])
	{
		if (is_positive_float(split[i]) == FAILURE)
			return (ft_free_char2(split), FAILURE);
		i++;
	}
	ft_free_char2(split);
	if (i != 3)
		return (FAILURE);
	return (SUCCESS);
}

t_binary_result	is_positive_int_three_dimensional(char *element)
{
	char	**split;
	int		i;

	if (has_2_commas(element) == FALSE)
		return (FAILURE);
	split = ft_split(element, ',');
	i = 0;
	while (split[i])
	{
		if (is_positive_int(split[i]) == FAILURE)
			return (ft_free_char2(split), FAILURE);
		i++;
	}
	ft_free_char2(split);
	if (i != 3)
		return (FAILURE);
	return (SUCCESS);
}
