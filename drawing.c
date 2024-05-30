/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:44:22 by anarama           #+#    #+#             */
/*   Updated: 2024/05/30 19:49:54 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void isometric_transform(int *x, int *y, int origin_x, int origin_y)
{
    const double angle = M_PI / 6;
    const int temp_x = *x - origin_x;
    const int temp_y = *y - origin_y;
    const int iso_x = temp_x * cos(angle) - temp_y * sin(angle);
    const int iso_y = temp_x * sin(angle) + temp_y * cos(angle);

    *x = iso_x + origin_x;
    *y = iso_y + origin_y;
}

int	define_step(const int a, const int b)
{
	if (a < b)
		return 1;
	else if (a > b)
		return -1;
	else
		return 0;
}

void draw_line(t_mlx *mlx, t_line *line, unsigned long color)
{
	const int step_x = define_step(line->x0, line->x1);
	const int step_y = define_step(line->y0, line->y1);
	const int dx = abs(line->x1 - line->x0);
	const int dy = abs(line->y1 - line->y0);
	int error;
	int x1;
	int y1;

	error = 0;
	x1 = line->x0;
	y1 = line->y0;
	while (1)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, x1, y1 , color);
		if (x1 == line->x1 && y1 == line->y1)
			break ;
		error = abs(x1 - line->x0) * dy - abs(y1 - line->y0) * dx;
		if (step_x && !error)
		{
			x1 += step_x;
		}
		else if (step_y && !error)
		{
			y1 += step_y;
		}
		else if (error < 0)
		{
			x1 += step_x;
		}
		else if (error > 0)
			y1 += step_y;
	}
}

void	draw_plane(t_mlx *mlx, t_line *line, t_map *map, int step)
{
	int save_x;
	int save_y;
	int i;
	int j;
	int	src_x;
	int src_y;
	unsigned long default_color = 0xFFFFFF;
	
	src_x = line->x0;
	src_y = line->y0;
	i = 0;
	while (i <= map->width)
	{
		j = 0;
		while (j <= map->length)
		{
			line->x1 = line->x0 + step;
			line->y1 = line->y0;
			isometric_transform(&(line->x1), &(line->y1), line->x0, line->y0);
			save_x = line->x1;
			save_y = line->y1;
			if (j < map->length && i < map->width)
				draw_line(mlx, line, map->colors[i][j]);
			else if (j < map->length && i == map->width)
				draw_line(mlx, line, default_color);
			line->x1 = line->x0;
			line->y1 = line->y0 + step;
			isometric_transform(&(line->x1), &(line->y1), line->x0, line->y0);
			if (i < map->width && j < map->length)
				draw_line(mlx, line, map->colors[i][j]);
			else if (i < map->width && j == map->length)
				draw_line(mlx, line, default_color);
			line->x0 = save_x;
			line->y0 = save_y;
			j++;
		}
		line->x0 = src_x;
		line->y0 = src_y;
		line->x1 = line->x0;
		line->y1 = line->y0 + step;
		isometric_transform(&(line->x1), &(line->y1), line->x0, line->y0);
		src_x = line->x1;
		src_y = line->y1;
		if (i < map->width && j < map->length)
			draw_line(mlx, line, map->colors[i][j]);
		else if (i < map->width && j == map->length)
			draw_line(mlx, line, default_color);
		line->x0 = line->x1;
		line->y0 = line->y1;
		i++;
	}
}
