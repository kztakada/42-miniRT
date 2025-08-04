/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:34:20 by katakada          #+#    #+#             */
/*   Updated: 2025/08/04 14:04:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "minirt.h"
# include <stdlib.h>
# include <time.h>

# define F_MSG "Bonus mode enabled\n"

// prototype
t_binary_result	stbi_data_to_color(unsigned char *img_data, int width,
					int height, t_texture *c_texture);

#endif