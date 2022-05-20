/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int str_cmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		if (s1[i] == 0 || s2[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

char *str_chr(const char *s, int c)
{
    if (s == 0)
        return (0);
    while (s[0] && s[0] != (char)c)
        s++;
    if (s[0] == (char)c)
        return ((char *)s);
    return (0);
}

int modify_color(t_map *map)
{
	int i = 0;
	int j = 0;

	while (i < map->nb_line)
	{
		while (j < map->nb_col)
		{
			if ((map->coord[i * map->nb_col + j].c == MY_GREEN) ||
			(map->coord[i * map->nb_col + j].c == MY_YELLOW) ||
			(map->coord[i * map->nb_col + j].c == MY_BLUE) ||
			(map->coord[i * map->nb_col + j].c == MY_PINK))
				map->coord[i * map->nb_col + j].c = map->color;
			j++;
		}
		j = 0;
		i++;
	}
	return(0);
}

int reset_color(t_map *map)
{
	int i = 0;
	int j = 0;

	while (i < map->nb_line)
	{
		while (j < map->nb_col)
		{
			if (map->coord[i * map->nb_col + j].c == map->color)
				map->coord[i * map->nb_col + j].c = DEFAULT;
			j++;
		}
		j = 0;
		i++;
	} 
	return(0);
}

int find_color(char *s, t_map *map)
{
	char *color;

	color = str_chr(s, 'x');
	if (color == 0)
		return (map->color);
	color++;
	if (str_cmp(color, "FFFFFF", 6) || str_cmp(color, "ffffff", 6))
		return (WHITE);
	if (str_cmp(color, "802020", 6))
		return (BORDEAUX);
	if (str_cmp(color, "FF0000", 6) || str_cmp(color, "ff0000", 6))
		return (RED);
	if (str_cmp(color, "00FF00", 6) || str_cmp(color, "ff00", 4))
		return (GREEN);
	if (str_cmp(color, "0000FF", 6) || str_cmp(color, "ff", 2))
		return (BLUE);
	else
		return(map->color);
}
