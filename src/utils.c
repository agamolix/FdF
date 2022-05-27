/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:43:42 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/27 12:46:37 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	tern(int i, int rtrue, int rfalse)
{
	if (i)
		return (rtrue);
	return (rfalse);
}

float	tern_f(int i, float rtrue, float rfalse)
{
	if (i)
		return (rtrue);
	return (rfalse);
}

void	free_split(char **element, char *line)
{
	int	i;

	i = 0;
	while (element[i])
	{
		free(element[i]);
		i++;
	}
	free(element);
	free(line);
}

int	str__cmp(const char *s1, const char *s2)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (s1[i])
	{
		res = s1[i] - s2[i];
		if (res != 0)
			return (res);
		if (s1[i] == 0 || s2[i] == 0)
			return (0);
		i++;
	}
	return (res);
}
