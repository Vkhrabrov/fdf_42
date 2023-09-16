/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:42:04 by vkhrabro          #+#    #+#             */
/*   Updated: 2023/09/16 20:09:46 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	read_file_3(t_win *data, char ***nums, int *j, int fd)
{
	char	*line;

	data->t = 0;
	while (get_next_line(fd, &line))
	{
		*nums = ft_split(line, ' ');
		data->z_matrix[data->t] = (int *)malloc(sizeof(int)
				* (data->width + 1));
		if (!data->z_matrix[data->t])
			exit(safe_exit(data, 1));
		*j = 0;
		while ((*nums)[*j])
		{
			data->z_matrix[data->t][*j] = ft_atoi((*nums)[*j]);
			free((*nums)[*j]);
			(*j)++;
		}
		free(*nums);
		free(line);
		data->t++;
	}
}

void	read_file_2(char *file_name, t_win *data, char *line, int fd)
{
	int		fd1;
	char	**nums;
	int		j;

	nums = NULL;
	j = 0;
	while (get_next_line(fd, &line))
	{
		data->height++;
		free(line);
	}
	close(fd);
	data->z_matrix = (int **)malloc(sizeof(int *) * data->height);
	if (!data->z_matrix)
		exit(safe_exit(data, 1));
	fd1 = open(file_name, O_RDONLY, 0);
	read_file_3(data, &nums, &j, fd1);
	close(fd1);
}

void	read_file(char *file_name, t_win *data)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY, 0);
	if (fd == -1)
	{
		write(1, "File doesn't exist or you have no rights to read it\n", 52);
		exit(1);
	}
	if (!get_next_line(fd, &line))
	{
		close(fd);
		write(1, "File is empty\n", 14);
		exit(1);
	}
	data->height = 0;
	data->width = 0;
	if (line)
	{
		data->width = ft_word_count(line, ' ');
		data->height = 1;
		free(line);
	}
	read_file_2(file_name, data, line, fd);
}

void	overlay(t_win *data)
{
	if (data->image.projection == 1)
	{
		mlx_string_put(data->image.win->mlx_ptr, data->image.win->win_ptr,
			900, 735, COLOR_PINK, "Change projection to parallel: 'P'");
		mlx_string_put(data->image.win->mlx_ptr, data->image.win->win_ptr,
			data->window_width / 2 - 100, 3,
			COLOR_PINK, "Isometric projection");
	}
	else
	{
		mlx_string_put(data->image.win->mlx_ptr, data->image.win->win_ptr,
			900, 735, COLOR_PINK, "Change projection to isoteric: 'I'");
		mlx_string_put(data->image.win->mlx_ptr, data->image.win->win_ptr,
			data->window_width / 2 - 100, 3, COLOR_PINK, "Parallel projection");
	}
	mlx_string_put(data->image.win->mlx_ptr,
		data->image.win->win_ptr, 15, 10, COLOR_PINK, "Zoom in: '+'");
	mlx_string_put(data->image.win->mlx_ptr,
		data->image.win->win_ptr, 15, 30, COLOR_PINK, "Zoom out: '-'");
	mlx_string_put(data->image.win->mlx_ptr,
		data->image.win->win_ptr, 15, 715, COLOR_PINK, "Scale up: 'S'");
	mlx_string_put(data->image.win->mlx_ptr,
		data->image.win->win_ptr, 15, 735, COLOR_PINK, "Scale down: 'D'");
}

int	main(int argc, char **argv)
{
	t_win	*data;

	(void)argc;
	data = (t_win *)malloc(sizeof(t_win));
	if (!data)
		exit(1);
	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".fdf", 4) != 0)
	{
		free(data);
		write(1, "Invalid arguments", 17);
		write(1, "\n", 1);
		exit(1);
	}
	starting_image_window(data);
	read_file(argv[1], data);
	drawing_set(data);
	mlx_put_image_to_window(data->image.win->mlx_ptr,
		data->image.win->win_ptr, data->image.img_ptr, 0, 0);
	overlay(data);
	mlx_key_hook(data->win_ptr, key_handle, data);
	mlx_hook(data->win_ptr, 17, 0, exit_program, data);
	mlx_loop(data->mlx_ptr);
	safe_exit(data, 0);
	return (0);
}
