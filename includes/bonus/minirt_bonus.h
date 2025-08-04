/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:34:20 by katakada          #+#    #+#             */
/*   Updated: 2025/08/05 00:48:13 by katakada         ###   ########.fr       */
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
t_binary_result	config_triangle(char **line_element, t_obj *obj);
t_binary_result	config_torus(char **line_element, t_obj *obj);
t_binary_result	config_cone(char **line_element, t_obj *obj);
t_binary_result	set_material_bonus(t_obj *obj, char **line_element,
					int start_index);
t_binary_result	format_check_triangle(char **line_element);
t_binary_result	format_check_torus(char **line_element);
t_binary_result	format_check_cone(char **line_element);
#endif