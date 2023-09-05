/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:43:28 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/05 22:18:52 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "float.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <ctype.h>

# define COLOR_BLACK       0x000000
# define COLOR_WHITE       0xFFFFFF
# define COLOR_RED         0xFF0000
# define COLOR_GREEN       0x00FF00
# define COLOR_BLUE        0x0000FF
# define COLOR_YELLOW      0xFFFF00
# define COLOR_CYAN        0x00FFFF
# define COLOR_MAGENTA     0xFF00FF
# define COLOR_GRAY        0x808080
# define COLOR_LIGHT_GRAY  0xC0C0C0
# define COLOR_DARK_GRAY   0x404040
# define COLOR_ORANGE      0xFFA500
# define COLOR_PINK        0xFFC0CB
# define COLOR_BROWN       0xA52A2A
# define COLOR_PURPLE      0x800080

# define KEY_I 34
# define KEY_P 35

# define S_WIDTH 1280
# define S_HEIGHT 768

typedef struct s_win	t_win;

typedef struct s_img
{
	t_win	*win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
	float	zoom;
	int		color;
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	factor;
	int		projection;
}			t_img;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
	int		window_height;
	int		window_width;
	int		**z_matrix;
	float	map_min_x;
	float	map_max_x;
	float	map_min_y;
	float	map_max_y;
	float	offset_x;
	float	offset_y;
	t_img	image;
	float	center_map_x;
	float	center_map_y;
	float	center_window_x;
	float	center_window_y;
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	z;
	float	z1;
	int		t;
}			t_win;

typedef struct s_square {
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size;
	int					color;
}		t_square;

void	new_program(int w, int h, char *str, t_win *data);
t_img	new_img(int w, int h, t_win *window);
void	put_pixel_img(t_img img, int x, int y, int color);
int		exit_tutorial(t_win *window);
void	bresenham(t_win *data, t_img image, int do_draw);
void	draw(t_win *data, t_img image, int do_draw);
int		key_handle(int keycode, t_win *data);
void	recenter_map(t_win *data);
void	re_scaling(t_win *data);
void	clear_image(t_img *img, int color);
void	put_pixel_img(t_img img, int x, int y, int color);
int		ft_word_count(const char *s, char c);
void	scaling_factor_2(t_win *data, float height_range);
void	scaling_factor(t_win *data);
void	recenter_map(t_win *data);
void	re_scaling(t_win *data);
void	drawing_set(t_win *data);
int		starting_image_window(t_win *data);
int		exit_program(t_win *window);
float	mod(float i);
int		max_macros(float a, float b);
float	conversion(int angle);
int		safe_exit(t_win *data, int value);
void	overlay(t_win *data);
int		safe_exit(t_win *data, int value);

#endif
