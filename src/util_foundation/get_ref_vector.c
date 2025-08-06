/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ref_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:26:26 by katakada          #+#    #+#             */
/*   Updated: 2025/08/05 23:28:10 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	up_dir(void)
{
	t_vector	up;

	up.x = 0.0F;
	up.y = 1.0F;
	up.z = 0.0F;
	return (up);
}

t_vector	right_dir(void)
{
	t_vector	right;

	right.x = 1.0F;
	right.y = 0.0F;
	right.z = 0.0F;
	return (right);
}
