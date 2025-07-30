/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:09:11 by katakada          #+#    #+#             */
/*   Updated: 2025/07/29 22:57:29 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

t_binary_result	put_out_failure(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return (FAILURE);
}

t_vector	put_out_error_vector(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return ((t_vector){0.0F, 0.0F, 0.0F});
}

t_color	put_out_error_color(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return ((t_color){0.0F, 0.0F, 0.0F});
}

t_hit	put_out_error_hit(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return ((t_hit){FALSE, {0.0F, 0.0F, 0.0F}, {0.0F, 0.0F, 0.0F}, 0.0F,
		{0.0F, 0.0F, 0.0F}, {0.0F, 0.0F, 0.0F}});
}

t_binary_result	put_out_format_error(char *type, char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_FORMAT, STDERR_FILENO);
	ft_putstr_fd(type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return (FAILURE);
}