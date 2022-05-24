/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:12:13 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:59:46 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	display_keys(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 20, data->map.color,
		"Fdf keys:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 50, data->map.color,
		"Arrow keys: translate x/y axis");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 70, data->map.color,
		"Q / A: up & down peaks");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 90, data->map.color,
		"W / S: clockwise & anti-clockwise rotation");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 110, data->map.color,
		"Z / X: left & right point of view");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 130, data->map.color,
		"E / D: diagonal swing");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 150, data->map.color,
		"R / F: zoom in & out");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 170, data->map.color,
		"I: reset initial parameters");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 190, data->map.color,
		"C: change color");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 210, data->map.color,
		"Esc: exit");
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
	data->map.x1 = -data->map.cube * (float)(data->map.nb_col - 1) / 2;
	data->map.y1 = -data->map.cube * (float)(data->map.nb_line - 1) / 2;
	data->map.r = data->map.r0;
	data->map.alt = (float)MAP_ALT / data->map.max_z;
	reset_color(&data->map);
	data->map.color = DEFAULT;
}

int	key_released(int key, t_data *data)
{
	if (key == 34)
		key_init(data);
	if (key == 15)
	{
		data->map.cube = data->map.cube * tern(data->map.cube < 300, 2, 1);
		data->map.alt = data->map.alt * tern(data->map.cube < 300, 2, 1);
		data->map.x1 = -data->map.cube * (float)(data->map.nb_col - 1) / 2;
		data->map.y1 = -data->map.cube * (float)(data->map.nb_line - 1) / 2;
	}
	if (key == 3)
	{
		if (data->map.cube > 2)
		{
			data->map.cube = data->map.cube / 2;
			data->map.alt /= 2;
		}
		data->map.x1 = -data->map.cube * (float)(data->map.nb_col - 1) / 2;
		data->map.y1 = -data->map.cube * (float)(data->map.nb_line - 1) / 2;
	}
	if (key == 8)
		key_color(data);
	if (key == 53)
		exit_clean(data);
	render(data);
	return (0);
}

int	key_down(int key, t_data *data)
{
	if (key == 123 || key == 124)
		data->map.x1 = data->map.x1 + tern(key == 124, 5, -5);
	if (key == 125 || key == 126)
		data->map.y1 = data->map.y1 + tern(key == 125, 5, -5);
	if (key == 12)
		data->map.alt = data->map.alt + tern_f(data->map.max_z == 0, 0,
				(float)MAP_ALT / data->map.max_z / 2);
	if (key == 0)
		data->map.alt = data->map.alt - tern_f(data->map.max_z == 0, 0,
				(float)MAP_ALT / data->map.max_z / 2);
	if (key == 13 || key == 1)
		data->map.r = data->map.r + tern_f(key == 13, 0.2, -0.2);
	if (key == 14 || key == 2)
		data->map.scale = data->map.scale + tern_f(key == 14, -0.25, 0.25);
	if (key == 6)
		data->map.orient = tern(data->map.orient == -10, -10,
				data->map.orient - 1);
	if (key == 7)
		data->map.orient = tern(data->map.orient == 10, 10,
				data->map.orient + 1);
	render (data);
	return (0);
}
