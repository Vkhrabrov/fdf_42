/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:21:20 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/02 23:49:31 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	conversion(int angle)
{
	float	luch;

	luch = (angle * M_PI) / 180;
	return (luch);
}

void	isometric(float *x, float *y, int z)
{
	float	x_copy;

	x_copy = *x;
	*x = (*x - *y) * cos(conversion(30));
	*y = (x_copy + *y) * sin(conversion(30)) - z;
}

void	bresenham_parameters_calculating(t_win *data, t_img *image)
{
	if (image->projection == 1)
	{
		isometric(&image->x, &image->y, data->z);
		isometric(&image->x1, &image->y1, data->z1);
	}
	data->x = image->zoom * image->x + data->offset_x;
	data->x1 = image->zoom * image->x1 + data->offset_x;
	data->y = image->zoom * image->y + data->offset_y;
	data->y1 = image->zoom * image->y1 + data->offset_y;
	if (data->x < data->map_min_x)
		data->map_min_x = data->x;
	if (data->x > data->map_max_x)
		data->map_max_x = data->x;
	if (data->y < data->map_min_y)
		data->map_min_y = data->y;
	if (data->y > data->map_max_y)
		data->map_max_y = data->y;
	if (data->z || data->z1)
		image->color = 0xe80c0c;
	else
		image->color = 0xffffff;
}

void	bresenham(t_win *data, t_img image, int do_draw)
{
	float	x_step;
	float	y_step;
	int		max;

	data->z = data->z_matrix[(int)image.y][(int)image.x];
	data->z1 = data->z_matrix[(int)image.y1][(int)image.x1];
	data->z = data->z * image.factor;
	data->z1 = data->z1 * image.factor;
	bresenham_parameters_calculating(data, &image);
	x_step = data->x1 - data->x;
	y_step = data->y1 - data->y;
	max = max_macros(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	if (do_draw)
	{
		while ((int)(data->x - data->x1) || (int)(data->y - data->y1))
		{
			put_pixel_img(image, data->x, data->y, image.color);
			data->x += x_step;
			data->y += y_step;
		}
	}
}

void	draw(t_win *data, t_img image, int do_draw)
{
	image.y = 0;
	while (image.y < data->height)
	{
		image.y1 = image.y + 1;
		image.x = 0;
		while (image.x < data->width)
		{
			if (image.x < (*data).width - 1)
			{
				image.x1 = image.x + 1;
				image.y1 = image.y;
				bresenham(data, image, do_draw);
			}
			if (image.y < (*data).height - 1)
			{
				image.x1 = image.x;
				image.y1 = image.y + 1;
				bresenham(data, image, do_draw);
			}
			image.x++;
		}
		image.y++;
	}
}
