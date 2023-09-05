/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:06:41 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/03 00:07:58 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	max_macros(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	zoom_in(t_win *data)
{
	data->image.zoom *= 1.1;
	data->offset_x = 0;
	data->offset_y = 0;
	data->map_min_x = FLT_MAX;
	data->map_max_x = FLT_MIN;
	data->map_min_y = FLT_MAX;
	data->map_max_y = FLT_MIN;
	draw(data, data->image, 0);
	recenter_map(data);
	clear_image(&data->image, 0);
	draw(data, data->image, 1);
	mlx_put_image_to_window(data->image.win->mlx_ptr, data->image.win->win_ptr,
		data->image.img_ptr, 0, 0);
	overlay(data);
}

void	zoom_out(t_win *data)
{
	data->image.zoom /= 1.1;
	data->offset_x = 0;
	data->offset_y = 0;
	data->map_min_x = FLT_MAX;
	data->map_max_x = FLT_MIN;
	data->map_min_y = FLT_MAX;
	data->map_max_y = FLT_MIN;
	draw(data, data->image, 0);
	recenter_map(data);
	clear_image(&data->image, 0);
	draw(data, data->image, 1);
	mlx_put_image_to_window(data->image.win->mlx_ptr, data->image.win->win_ptr,
		data->image.img_ptr, 0, 0);
	overlay(data);
}

void	key_handle_ext(t_win *data)
{
	data->offset_x = 0;
	data->offset_y = 0;
	data->map_min_x = FLT_MAX;
	data->map_max_x = FLT_MIN;
	data->map_min_y = FLT_MAX;
	data->map_max_y = FLT_MIN;
	data->image.zoom = 1;
	drawing_set(data);
	mlx_put_image_to_window(data->image.win->mlx_ptr, data->image.win->win_ptr,
		data->image.img_ptr, 0, 0);
	overlay(data);
}

int	key_handle(int keycode, t_win *data)
{
	if (keycode == KEY_I)
		data->image.projection = 1;
	if (keycode == KEY_P)
		data->image.projection = 0;
	if (keycode == 1)
		data->image.factor += 0.1;
	if (keycode == 2)
		data->image.factor -= 0.1;
	if (keycode == 69)
	{
		zoom_in(data);
		return (1);
	}
	if (keycode == 78)
	{
		zoom_out(data);
		return (1);
	}
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(safe_exit(data, 0));
	}
	key_handle_ext(data);
	return (0);
}
