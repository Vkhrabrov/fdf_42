/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:24:25 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/13 00:14:15 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	recenter_map(t_win *data)
{
	data->center_map_x = (data->map_min_x + data->map_max_x) / 2;
	data->center_map_y = (data->map_min_y + data->map_max_y) / 2;
	data->center_window_x = data->window_width / 2;
	data->center_window_y = data->window_height / 2;
	data->offset_x = data->center_window_x - data->center_map_x;
	data->offset_y = data->center_window_y - data->center_map_y;
}

void	re_scaling(t_win *data)
{
	float	map_width;
	float	map_height;
	float	width_scale;
	float	height_scale;
	float	scale_factor;

	map_width = data->map_max_x - data->map_min_x;
	map_height = data->map_max_y - data->map_min_y;
	width_scale = S_WIDTH / map_width * 0.9;
	height_scale = S_HEIGHT / map_height * 0.9;
	scale_factor = min(width_scale, height_scale);
	data->image.zoom = scale_factor;
}

void	scaling_factor_2(t_win *data, float height_range)
{
	if (height_range >= 0 && height_range <= 10)
		data->image.factor = 0.1;
	else if (height_range >= 11 && height_range <= 25)
		data->image.factor = 1;
	else if (height_range > 25)
		data->image.factor = 0.3;
}

void	scaling_factor(t_win *data)
{
	int		i;
	int		j;
	float	max_z;
	float	min_z;
	float	height_range;

	max_z = data->z_matrix[0][0];
	min_z = data->z_matrix[0][0];
	i = 0;
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			if (data->z_matrix[j][i] > max_z)
				max_z = data->z_matrix[j][i];
			if (data->z_matrix[j][i] < min_z)
				min_z = data->z_matrix[j][i];
			j++;
		}
		i++;
	}
	height_range = max_z - min_z;
	scaling_factor_2(data, height_range);
}
