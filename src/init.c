/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:01:05 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:55:16 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	populate_map(t_map *map, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**element;

	i = 0;
	j = 0;
	map->max_z = 0;
	while (i < map->nb_line)
	{
		line = get_next_line(fd);
		while (j < map->nb_col)
		{
			element = my_split(line, ' ');
			map->coord[i * map->nb_col + j].x = j;
			map->coord[i * map->nb_col + j].y = i;
			map->coord[i * map->nb_col + j].z = my_atoi(element[j]);
			map->coord[i * map->nb_col + j].c = find_color(element[j], map);
			map->max_z = fmax(map->max_z, my_atoi(element[j]));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	calc_map(t_map *map, int fd)
{
	char	*line;
	char	**element;
	int		max_col;

	map->nb_line = 0;
	map->nb_col = 0;
	line = get_next_line(fd);
	while (line != 0)
	{
		element = my_split(line, ' ');
		max_col = 0;
		while (element[max_col] && element[max_col][0] != 10)
			max_col++;
		map->nb_col = tern(max_col > map->nb_col, max_col, map->nb_col);
		map->nb_line++;
		line = get_next_line(fd);
	}
	map->coord = malloc((map->nb_col * map->nb_line + 1) * sizeof(t_coord));
	map->color = DEFAULT;
	return (0);
}

int	init_map(t_map *map)
{
	map->x_center = WIN_WIDTH / 2;
	map->y_center = WIN_HEIGHT / 2;
	map->scale0 = 2;
	map->orient0 = 5;
	map->r0 = 0;
	map->cube0 = fmin(map->x_center / (map->nb_col - 1), map->y_center
			/ (map->nb_line - 1));
	map->scale = map->scale0;
	map->orient = map->orient0;
	map->r = map->r0;
	map->cube = map->cube0;
	map->alt = tern_f(map->max_z == 0, 0, (float)MAP_ALT / map->max_z);
	map->x1 = -map->cube * (float)(map->nb_col - 1) / 2;
	map->y1 = -map->cube * (float)(map->nb_line - 1) / 2;
	return (0);
}

int	open_file(t_map *map, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	calc_map(map, fd);
	close (fd);
	fd = open(path, O_RDONLY);
	populate_map(map, fd);
	close (fd);
	init_map(map);
	return (0);
}

int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!data->win_ptr)
		return (1);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img_ptr)
		return (1);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (0);
}
