/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 23:22:26 by katakada          #+#    #+#             */
/*   Updated: 2025/07/25 23:25:48 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include "minirt.h"
# include <pthread.h>

typedef struct s_thread_data
{
	pthread_t	id;
	int			num;
	t_scene		*scene;
}				t_thread_data;
#endif