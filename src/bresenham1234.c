/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham1234.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:45:48 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:06:21 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	trace_1(t_line *l, t_img *img)
{
	int	e;
	int	mid;

	mid = l->x2 / 2 + l->x1 / 2;
	e = l->dx;
	l->dx = e * 2;
	l->dy = l->dy * 2;
	while (l->x1 <= l->x2)
	{
		if (l->x1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		e = e - l->dy;
		if (e < 0)
		{
			l->y1 += 1;
			e = e + l->dx;
		}
		l->x1 += 1;
	}
}

void	trace_2(t_line *l, t_img *img)
{
	int	e;
	int	mid;

	mid = l->y2 / 2 + l->y1 / 2;
	e = l->dy;
	l->dy = e * 2;
	l->dx = l->dx * 2;
	while (l->y1 <= l->y2)
	{
		if (l->y1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		e = e - l->dx;
		if (e < 0)
		{
			l->x1 += 1;
			e = e + l->dy;
		}
		l->y1 += 1;
	}
}

void	trace_3(t_line *l, t_img *img)
{
	int	e;
	int	mid;

	mid = l->y2 / 2 + l->y1 / 2;
	e = l->dy;
	l->dy = e * 2;
	l->dx = l->dx * 2;
	while (l->y1 <= l->y2)
	{
		if (l->y1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		e = e + l->dx;
		if (e <= 0)
		{
			l->x1 -= 1;
			e = e + l->dy;
		}
		l->y1 += 1;
	}
}

void	trace_4(t_line *l, t_img *img)
{
	int	e;
	int	mid;

	mid = l->x2 / 2 + l->x1 / 2;
	e = l->dx;
	l->dx = e * 2;
	l->dy = l->dy * 2;
	while (l->x1 >= l->x2)
	{
		if (l->x1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		e = e + l->dy;
		if (e >= 0)
		{
			l->y1 += 1;
			e = e + l->dx;
		}
		l->x1 -= 1;
	}
}
