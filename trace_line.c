/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int iso_line(t_line *l, t_map *map)
{
	if (map->orient >= 0)
	{
		l->x1 = l->xo1 - l->yo1;
		l->y1 = (l->xo1 + l->yo1) / map->scale;
		l->x2 = l->xo2 - l->yo2;
		l->y2 = (l->xo2 + l->yo2) / map->scale;
	}
	else
	{
		l->x1 = l->xo1 + l->yo1;
		l->y1 = (l->yo1 - l->xo1) / map->scale;
		l->x2 = l->xo2 + l->yo2;
		l->y2 = (l->yo2 - l->xo2) / map->scale;
	}
	return (0);
}

int persp_line(t_line *l, t_map *map)
{
	int or;

	or = map->orient;
	if (or < 0)
		or = -or;
	l->x1 = l->x1 * or / 10 + l->xo1 * (10 - or) / 10;
	l->y1 = l->y1 * or / 10 + l->yo1 * (10 - or) / 10;
	l->x2 = l->x2 * or / 10 + l->xo2 * (10 - or) / 10;
	l->y2 = l->y2 * or / 10+ l->yo2 * (10 - or) / 10;
	return(0);
}

int rot_line(t_line *l, t_map *map)
{
	int temp_x;
	int temp_y;

	temp_x = l->x1;
	temp_y = l->y1;
	l->x1 = temp_x * cos(map->r) - temp_y * sin(map->r);
	l->y1 = temp_x * sin(map->r) + temp_y * cos(map->r);
	temp_x = l->x2;
	temp_y = l->y2;
	l->x2 = temp_x * cos(map->r) - temp_y * sin(map->r);
	l->y2 = temp_x * sin(map->r) + temp_y * cos(map->r);
	return (0);
}

int center_line(t_line *l, t_map *map)
{
	l->x1 = l->x1 + map->x_center;
	l->y1 = l->y1 + map->y_center - l->z1;
	l->x2 = l->x2 + map->x_center;
	l->y2 = l->y2 + map->y_center - l->z2;
	l->dx = l->x2 - l->x1;
	l->dy = l->y2 - l->y1;
	return (0);
}

int trace_line(t_line *l, t_img *img, t_map *map)
{
	iso_line(l, map);
	persp_line(l, map);
	rot_line(l, map);
	center_line(l, map);
	trace(l, img);
	return (0);
}
