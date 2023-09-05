/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:35:54 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/05 22:21:45 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_program(t_win *window)
{
	if (window)
		mlx_destroy_window (window->mlx_ptr, window->win_ptr);
	exit(safe_exit(window, 0));
}

void	drawing_set(t_win *data)
{
	clear_image(&data->image, 0);
	draw(data, data->image, 0);
	re_scaling(data);
	draw(data, data->image, 0);
	recenter_map(data);
	draw(data, data->image, 1);
}

int	safe_exit(t_win *data, int value)
{
	int	k;

	k = 0;
	while (k < data->height)
	{
		if (data->z_matrix[k])
			free(data->z_matrix[k]);
		k++;
	}
	free(data->z_matrix);
	free(data);
	return (value);
}

int	starting_image_window(t_win *data)
{
	data->map_min_x = FLT_MAX;
	data->map_max_x = FLT_MIN;
	data->map_min_y = FLT_MAX;
	data->map_max_y = FLT_MIN;
	new_program(S_WIDTH, S_HEIGHT, "New Window", data);
	if (!data->mlx_ptr || !data->win_ptr)
		exit(safe_exit(data, 1));
	data->image = new_img(S_WIDTH, S_HEIGHT, data);
	data->image.zoom = 1;
	return (0);
}

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
