/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:43:42 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:58:30 by atrilles         ###   ########.fr       */
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
