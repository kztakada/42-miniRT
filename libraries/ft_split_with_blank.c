/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_blank.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 06:53:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/07/25 07:18:04 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_row_count(char const *s)
{
	int	row;

	row = 0;
	while (*s)
	{
		if (*s != 32 && (*s < 9 || *s > 13))
		{
			row++;
			while ((*s != 32 && (*s < 9 || *s > 13))
				&& *s != '\0')
				s++;
		}
		else
			s++;
	}
	return (row);
}

static char	*ft_col_count(char const *s, int j)
{
	int		start;
	int		col;
	char	*res;
	char	*res_cpy;

	start = j;
	col = 0;
	while (s[j] && (s[j] != 32 && (s[j] < 9 || s[j] > 13)))
	{
		col++;
		j++;
	}
	res = (char *)malloc(sizeof(char) * (col + 1));
	if (res == NULL)
		return (res);
	res_cpy = res;
	while (col-- > 0)
		*(res_cpy++) = s[start++];
	*res_cpy = '\0';
	return (res);
}

static char	**ft_free(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split_with_blank(char const *s)
{
	int		i;
	int		j;
	int		row;
	char	**ans;

	if (!s)
		return (0);
	row = ft_row_count(s);
	ans = (char **)malloc(sizeof(char *) * (row + 1));
	if (!ans)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < row)
	{
		while (s[j] && (s[j] == 32 || (s[j] >= 9 && s[j] <= 13)))
			j++;
		ans[i] = ft_col_count(s, j);
		if (!ans[i])
			return (ft_free(ans, i));
		while (s[j] && (s[j] != 32 && (s[j] < 9 || s[j] > 13)))
			j++;
	}
	ans[i] = NULL;
	return (ans);
}
