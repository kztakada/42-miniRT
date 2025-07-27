/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:56:27 by katakada          #+#    #+#             */
/*   Updated: 2025/07/27 21:09:59 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_first_light(t_scene_with_mlx *r_scene)
{
	if (r_scene->key.first_index_light == NULL)
		return ;
	r_scene->key.selected_light = r_scene->key.first_index_light;
	r_scene->key.selected_light_index = 0;
}

static void	set_last_light(t_scene_with_mlx *r_scene)
{
	int	last_index;

	if (r_scene->key.first_index_light == NULL)
		return ;
	last_index = ft_lstsize(r_scene->key.first_index_light) - 1;
	r_scene->key.selected_light = ft_lstlast(r_scene->key.first_index_light);
	r_scene->key.selected_light_index = last_index;
}

void	select_next_light(t_scene_with_mlx *r_scene)
{
	t_list	*next_light;

	if (r_scene->key.first_index_light == NULL)
		return ;
	r_scene->key.mode = LIGHT_MODE;
	if (r_scene->key.selected_light == NULL)
		return (set_first_light(r_scene));
	next_light = r_scene->key.selected_light->next;
	r_scene->key.selected_light_index++;
	if (next_light == NULL)
		return (set_first_light(r_scene));
	r_scene->key.selected_light = next_light;
}

void	select_prev_light(t_scene_with_mlx *r_scene)
{
	t_list	*prev_light;
	int		i;

	if (r_scene->key.first_index_light == NULL)
		return ;
	r_scene->key.mode = LIGHT_MODE;
	if (r_scene->key.selected_light == NULL)
		return (set_first_light(r_scene));
	if (r_scene->key.selected_light_index == 0)
		return (set_last_light(r_scene));
	i = 0;
	prev_light = r_scene->key.first_index_light;
	while (prev_light && i < r_scene->key.selected_light_index)
	{
		prev_light = prev_light->next;
		i++;
	}
	r_scene->key.selected_light_index--;
	if (prev_light == NULL)
		return (set_first_light(r_scene));
	r_scene->key.selected_light = prev_light;
}
