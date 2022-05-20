/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2022/02/03 16:27:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pix_on_img(t_img *img, int x, int y, int color)
{
	char    *pix;

    if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		pix = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pix = color;
	}
}

int	render(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.line_len, &data->img.endian);
	draw_horiz(&data->map, &data->img, &data->l);
	draw_vert(&data->map, &data->img, &data->l);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	display_keys(data);
	return (0);
}

int exit_error(t_data *data, char *error)
{
	int i;

	if (data->map.coord)
		free(data->map.coord);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	if (data->win_ptr)
		free(data->win_ptr);
	if (data->img.img_ptr)
		free(data->img.img_ptr);
    i = write(1, error, str_len(error));
    i = write(1, "\n", 1);
	return(i);
}

int exit_clean(t_data *data)
{
	free(data->map.coord);
	free(data->img.img_ptr);
	free(data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return(exit_error(&data, "error: no file"));
	if (open_file(&data.map, argv[1]))
		return(exit_error(&data, "error: invalid file"));
	if (init_mlx(&data))
        return (exit_error(&data, "error: could not init mlx"));
	render(&data);
	mlx_key_hook(data.win_ptr, &key_released, &data);
	mlx_hook(data.win_ptr, 2, (1L<<0), &key_down, &data);
	mlx_hook(data.win_ptr, 17, 0, &exit_clean, &data);
	mlx_loop(data.mlx_ptr);
}
