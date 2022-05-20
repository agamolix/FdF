/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhamUDLR.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void trace_LR(t_line *l, t_img *img, char c)
{
	int mid;

	mid = l->x2 / 2 + l->x1 / 2;
	if (c == 'R')
		while (l->x1 <= l->x2)
		{
			if (l->x1 <= mid)
				put_pix_on_img(img, l->x1, l->y1, l->c1);
			else
				put_pix_on_img(img, l->x1, l->y1, l->c2);
			l->x1 += 1;
		}
	if (c == 'L')
		while (l->x1 >= l->x2)
		{
			if (l->x1 <= mid)
				put_pix_on_img(img, l->x1, l->y1, l->c1);
			else
				put_pix_on_img(img, l->x1, l->y1, l->c2);
			l->x1 -= 1;
		}
}

void trace_UD(t_line *l, t_img *img, char c)
{
	int mid;

	mid = l->y2 / 2 + l->y1 / 2;
	if (c == 'U') 
		while (l->y1 <= l->y2)
		{
		if (l->y1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		l->y1 += 1;
		}
	if (c == 'D')
		while (l->y1 >= l->y2)
		{
		if (l->y1 <= mid)
			put_pix_on_img(img, l->x1, l->y1, l->c1);
		else
			put_pix_on_img(img, l->x1, l->y1, l->c2);
		l->y1 -= 1;
		}
}

void trace(t_line *l, t_img *img)
{
	if (l->x2 > l->x1 && l->y2 > l->y1 && l->dx >= l->dy) 
		trace_1(l, img);
	if (l->x2 > l->x1 && l->y2 > l->y1 && l->dx < l->dy) 
		trace_2(l, img);
	if (l->x2 > l->x1 && l->y2 < l->y1 && l->dx >= - l->dy)
		trace_8(l, img);
	if (l->x2 > l->x1 && l->y2 < l->y1 && l->dx < - l->dy) 
		trace_7(l, img);
	if (l->x2 < l->x1 && l->y2 > l->y1 && - l->dx >= l->dy) 
		trace_4(l, img);
	if (l->x2 < l->x1 && l->y2 > l->y1 && - l->dx < l->dy) 
		trace_3(l, img);
	if (l->x2 < l->x1 && l->y2 < l->y1 && l->dx <= l->dy) 
		trace_5(l, img);
	if (l->x2 < l->x1 && l->y2 < l->y1 && l->dx > l->dy) 
		trace_6(l, img);
	if (l->x2 > l->x1 && l->y1 == l->y2) 
		trace_LR(l, img, 'R');	
	if (l->x2 < l->x1 && l->y1 == l->y2) 
		trace_LR(l, img, 'L');	
	if (l->x1 == l->x2 && l->y2 > l->y1) 
		trace_UD(l, img, 'U');
	if (l->x1 == l->x2 && l->y2 < l->y1) 
		trace_UD(l, img, 'D');
}
