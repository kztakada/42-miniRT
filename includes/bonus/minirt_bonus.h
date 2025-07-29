/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:34:20 by katakada          #+#    #+#             */
/*   Updated: 2025/07/28 19:03:17 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt.h"
# include <stdlib.h>

# define F_MSG "Bonus mode enabled\n"

// prototype
int	stbi_data_to_color(unsigned char *img_data, int width, int height,
		t_texture *c_texture);

#endif