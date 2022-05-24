/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:27:09 by atrilles          #+#    #+#             */
/*   Updated: 2022/05/24 14:57:01 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "gnl.h"
# include "fdf.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 600
# define MAP_ALT 40

# define RED 0xFF0000
# define GREEN 0x00FF00
# define MY_GREEN 0x00FF01
# define BLUE 0x0000FF
# define MY_BLUE 0x0001FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define MY_YELLOW 0xFFFF01
# define BORDEAUX 0x802020
# define MY_PINK 0xFF68C4
# define DEFAULT MY_GREEN

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct t_coord
{
	int			x;
	int			y;
	int			z;
	int			c;
}	t_coord;

typedef struct s_map
{
	int			nb_line;
	int			nb_col;
	int			x_center;
	int			y_center;
	int			x1;
	int			y1;
	int			max_z;
	int			cube;
	int			cube0;
	double		r;
	double		r0;
	int			orient;
	int			orient0;
	float		scale;
	float		scale0;
	float		alt;
	int			color;
	t_coord		*coord;

}	t_map;

typedef struct s_line
{
	int		x1;
	int		y1;
	int		z1;
	int		c1;
	int		x2;
	int		y2;
	int		z2;
	int		c2;
	int		xo1;
	int		yo1;
	int		xo2;
	int		yo2;
	int		dx;
	int		dy;
}	t_line;

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	char	*str;
	t_line	l;
	t_map	map;
}	t_data;

//-----fdf-----
void	put_pix_on_img(t_img *img, int x, int y, int color);
int		render(t_data *data);
int		exit_clean(t_data *data);
int		exit_error(t_data *data, char *error);
int		main(int argc, char **argv);

//-----init-----
int		populate_map(t_map *map, int fd);
int		calc_map(t_map *map, int fd);
int		init_map(t_map *map);
int		open_file(t_map *map, char *path);
int		init_mlx(t_data *data);

//-----coord-----
int		coord_line_horiz(t_line *l, t_map *map, int i, int j);
int		draw_horiz(t_map *map, t_img *img, t_line *l);
int		coord_line_vert(t_line *l, t_map *map, int i, int j);
int		draw_vert(t_map *map, t_img *img, t_line *l);

//-----trace-----
int		iso_line(t_line *l, t_map *map);
int		persp_line(t_line *l, t_map *map);
int		rot_line(t_line *l, t_map *map);
int		center_line(t_line *l, t_map *map);
int		trace_line(t_line *l, t_img *img, t_map *map);

//-----keys-----
void	display_keys(t_data *data);
void	key_color(t_data *data);
void	key_init(t_data *data);
int		key_released(int key, t_data *data);
int		key_down(int key, t_data *data);

//-----color-----
int		str_cmp(char *s1, char *s2, int n);
char	*str_chr(const char *s, int c);
int		modify_color(t_map *map);
int		reset_color(t_map *map);
int		find_color(char *s, t_map *map);

//-----bresenham-----
void	trace_1(t_line *l, t_img *img);
void	trace_2(t_line *l, t_img *img);
void	trace_3(t_line *l, t_img *img);
void	trace_4(t_line *l, t_img *img);
void	trace_5(t_line *l, t_img *img);
void	trace_6(t_line *l, t_img *img);
void	trace_7(t_line *l, t_img *img);
void	trace_8(t_line *l, t_img *img);
void	trace_lr(t_line *l, t_img *img, char c);
void	trace_ud(t_line *l, t_img *img, char c);
void	trace(t_line *l, t_img *img);

//-----split-----
int		str_len(char const *str);
char	*line(char const *str, char c);
char	*forward(char const *str, char c);
int		count(char const *str, char c);
char	**my_split(char const *s, char c);

//-----atoi-----
char	*remove_space(char *str);
int		convert(char *str, int len_nb, int sign);
int		calc_len_nb(char *str);
int		my_atoi(char *nptr);

//-----utils-----
int		tern(int i, int rtrue, int rfalse);
float	tern_f(int i, float rtrue, float rfalse);

#endif
