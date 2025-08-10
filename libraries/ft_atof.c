/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:01:40 by kharuya           #+#    #+#             */
/*   Updated: 2025/08/10 20:59:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	calc_decimal(char *str)
{
	float	decimal;
	int		decimal_place;

	decimal = 0.0f;
	decimal_place = 0;
	while (*str >= '0' && *str <= '9')
	{
		decimal_place++;
		decimal = decimal * 10.0f + (*str - '0');
		str++;
	}
	decimal = decimal / powf(10.0f, decimal_place);
	return (decimal);
}

float	ft_atof(char *str)
{
	float	sign;
	float	ans;

	sign = 1.0f;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1.0f;
		str++;
	}
	else if (*str == '+')
		str++;
	ans = 0.0f;
	while (*str >= '0' && *str <= '9')
	{
		ans = (ans * 10.0f) + (*str - '0');
		str++;
	}
	if (*str == '.')
		ans = ans + calc_decimal(++str);
	return (sign * ans);
}
