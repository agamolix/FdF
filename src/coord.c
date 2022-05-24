/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:44:04 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:05:37 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

#define RED 0xFF0000
#define GREEN 0x00FF00
#define MY_GREEN 0x00FF01
#define BLUE 0x0000FF
#define MY_BLUE 0x0001FF
#define WHITE 0xFFFFFF
#define YELLOW 0xFFFF00
#define MY_YELLOW 0xFFFF01
#define BORDEAUX 0x802020
#define MY_PINK 0xFF68C4
#define DEFAULT MY_GREEN

int	coord_line_horiz(t_line *l, t_map *map, int i, int j)
{
	l->xo1 = l->xo2;
	l->yo1 = l->yo2;
	l->z1 = l->z2;
	l->c1 = l->c2;
	l->xo2 = l->xo1 + map->cube;
	l->yo2 = l->yo1;
	l->z2 = map->coord[i * map->nb_col + j].z * map->alt;
	l->c2 = map->coord[i * map->nb_col + j].c;
	return (0);
}

int	draw_horiz(t_map *map, t_img *img, t_line *l)
{
	int	y1;
	int	i;
	int	j;

	y1 = map->y1;
	i = 0;
	while (i < map->nb_line)
	{
			j = 1;
		l->xo2 = map->x1;
		l->yo2 = y1;
		l->c2 = map->coord[i * map->nb_col].c;
		l->z2 = map->coord[i * map->nb_col].z * map->alt;
		while (j < map->nb_col)
		{
			coord_line_horiz(l, map, i, j);
			trace_line(l, img, map);
			j++;
		}
		i++;
		y1 = y1 + map->cube;
	}
	return (0);
}

int	coord_line_vert(t_line *l, t_map *map, int i, int j)
{
	l->xo1 = l->xo2;
	l->yo1 = l->yo2;
	l->c1 = l->c2;
	l->z1 = l->z2;
	l->xo2 = l->xo1;
	l->yo2 = l->yo1 + map->cube;
	l->z2 = map->coord[j * map->nb_col + i].z * map->alt;
	l->c2 = map->coord[j * map->nb_col + i].c;
	return (0);
}

int	draw_vert(t_map *map, t_img *img, t_line *l)
{	
	int	x1;
	int	i;
	int	j;

	x1 = map->x1;
	i = 0;
	while (i < map->nb_col)
	{
		j = 1;
		l->xo2 = x1;
		l->yo2 = map->y1;
		l->c2 = map->coord[i].c;
		l->z2 = map->coord[i].z * map->alt;
		while (j < map->nb_line)
		{
			coord_line_vert(l, map, i, j);
			trace_line(l, img, map);
			j++;
		}
		i++;
		x1 = x1 + map->cube;
	}
	return (0);
}
