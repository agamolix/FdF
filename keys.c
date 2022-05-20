/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void display_keys(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 20, data->map.color, "Fdf keys:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 50, data->map.color, "Arrow keys: translate x/y axis");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 70, data->map.color, "A / Q: up & down peaks");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 90, data->map.color, "Z / S: clockwise & anti-clockwise rotation");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 110, data->map.color, "W / X: left & right point of view");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 130, data->map.color, "E / D: diagonal swing");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 150, data->map.color, "R / F: zoom in & out");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 170, data->map.color, "I: reset initial parameters");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 190, data->map.color, "C: change color");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 210, data->map.color, "Esc: exit");
}

void	key_color(t_data *data)
{
	if (data->map.color == MY_GREEN)
		data->map.color = MY_YELLOW;
	else if (data->map.color == MY_YELLOW)
		data->map.color = MY_BLUE;
	else if (data->map.color == MY_BLUE)
		data->map.color = MY_PINK;
	else if (data->map.color == MY_PINK)
		data->map.color = MY_GREEN;
	modify_color(&data->map);
}

void	key_init(t_data *data)
{
	data->map.scale = data->map.scale0;
	data->map.orient = 5;
	data->map.cube = data->map.cube0;
	data->map.x1 = - data->map.cube * (float)(data->map.nb_col - 1) / 2;
	data->map.y1 = - data->map.cube * (float)(data->map.nb_line - 1) / 2;	
	data->map.r = data->map.r0;
	data->map.alt = (float)MAP_ALT / data->map.max_z;
	reset_color(&data->map);
	data->map.color = DEFAULT;
}

int	key_released(int key, t_data *data)
{
	if (key == 105)
		key_init(data);
	if (key == 114)
	{
		data->map.cube = data->map.cube * (data->map.cube < 300 ? 2 : 1);
		data->map.alt *= (data->map.cube < 300) ? 2 : 1;
		data->map.x1 = - data->map.cube * (float)(data->map.nb_col - 1) / 2;
		data->map.y1 = - data->map.cube * (float)(data->map.nb_line - 1) / 2;	
	}
	if (key == 102)
	{
		if (data->map.cube > 2)
		{
			data->map.cube = data->map.cube / 2;
			data->map.alt /= 2;
		}
		data->map.x1 = - data->map.cube * (float)(data->map.nb_col - 1) / 2;
		data->map.y1 = - data->map.cube * (float)(data->map.nb_line - 1) / 2;	
	}
	if (key == 99)
		key_color(data);
	if (key == 65307)
		exit_clean(data);
	render(data);
	return(0);
}

int	key_down(int key, t_data *data)
{
	if (key == 65363 || key == 65361)
		data->map.x1 += (key == 65363) ? 5 : -5;
	if (key == 65364 || key == 65362)
		data->map.y1 += (key == 65364) ? 5 : -5;
	if (key == 97)
		data->map.alt += data->map.max_z == 0 ? 0 : (float)MAP_ALT / data->map.max_z / 2;
	if (key == 113)
		data->map.alt -= data->map.max_z == 0 ? 0 : (float)MAP_ALT / data->map.max_z / 2;
	if (key == 122 || key == 115)
		data->map.r += (key == 122) ? 0.2 : - 0.2;
	if (key == 101 || key == 100)
		data->map.scale += (key == 101) ? - 0.25 : + 0.25;
	if (key == 119)
		data->map.orient = data->map.orient == -10 ? -10 : data->map.orient - 1;
	if (key == 120)
		data->map.orient = data->map.orient == 10 ? 10 : data->map.orient + 1;
	render(data);
	return(0);
}

