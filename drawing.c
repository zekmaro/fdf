/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:44:22 by anarama           #+#    #+#             */
/*   Updated: 2024/06/11 20:14:14 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void isometric_transform(int *x, int *y, int z)
{
    const double angle = M_PI / 6;
   	int temp_x = *x;
    int temp_y = *y;
	*x = (temp_x - temp_y) * cos(angle) + 1000;
	*y = (temp_x + temp_y) * sin(angle) - z + 300;
}

int	define_step(const int a, const int b)
{
	if (a < b)
		return 1;
	else if (a > b)
		return (-1);
	else
		return (0);
}

int get_red(unsigned long color) 
{
    return ((color >> 16) & 0xFF);
}

int get_green(unsigned long color) 
{
    return ((color >> 8) & 0xFF);
}

int get_blue(unsigned long color) 
{
    return (color & 0xFF);
}

void	initialise_rgb(t_color *color)
{
	color->red = get_red(color->color);
	color->green = get_green(color->color);
	color->blue = get_blue(color->color);
}

int	interpolate(int start_component, int end_component, t_map *map, int height)
{
	int result;
	const int dh = map->max_height - map->min_height;
	const int d_rgb = end_component - start_component;
	result = start_component + d_rgb * (height - map->min_height) / dh;
	return (result);
}

unsigned long	combine_rgb(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

unsigned long	calculate_gradient(t_color *color_start, t_color *color_end, t_map *map, int height)
{
	unsigned long result;
	int result_red;
	int result_green;
	int result_blue;

	result_red = interpolate(color_start->red, color_end->red, map, height);
	result_green = interpolate(color_start->green, color_end->green, map, height);
	result_blue = interpolate(color_start->blue, color_end->blue, map, height);
	result = combine_rgb(result_red, result_green, result_blue);
	return (result);
}

void draw_line(t_mlx *mlx, t_line *line, t_colors *colors, t_map *map, unsigned long color, int height, int dh)
{
	const int step_x = define_step(line->x0, line->x1);
	const int step_y = define_step(line->y0, line->y1);
	const int dx = abs(line->x1 - line->x0);
	const int dy = abs(line->y1 - line->y0);
	int error;
	int x0;
	int y0;

	int i = 0;
	if (dh < 0)
		dh = -1;
	else if (dh > 0)
		dh = 1;
	else
		dh = 0;
	error = 0;
	x0 = line->x0;
	y0 = line->y0;
	while (1)
	{
		if (i % 6 == 0 && dh)
			height += dh;
		color = calculate_gradient(colors->white, colors->red, map, height);
		mlx_pixel_put(mlx->mlx, mlx->win, x0, y0, color);
		if (x0 == line->x1 && y0 == line->y1)
			break ;
		error = abs(x0 - line->x0) * dy - abs(y0 - line->y0) * dx;
		if (step_x && !error)
		{
			x0 += step_x;
		}
		else if (step_y && !error)
		{
			y0 += step_y;
		}
		else if (error < 0)
		{
			x0 += step_x;
		}
		else if (error > 0)
			y0 += step_y;
		i++;
	}
}

void	draw_plane(t_mlx *mlx, t_line *line, t_map *map, t_colors *colors)
{
	int i;
	int j;
	int dh;
	
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (j < map->length - 1)
			{
				line->x0 = j * map->step;
				line->y0 = i * map->step;
				line->x1 = (j + 1) * map->step;
				line->y1 = i * map->step;
				isometric_transform(&(line->x0), &(line->y0) , map->grid[i][j]);
				isometric_transform(&(line->x1), &(line->y1) , map->grid[i][j + 1]);
				dh = map->grid[i][j + 1] - map->grid[i][j];
				draw_line(mlx, line, colors, map, map->colors[i][j], map->grid[i][j], dh);
			}
			if (i < map->width - 1)
			{
				line->x0 = j * map->step;
				line->y0 = i * map->step;
				line->x1 = j * map->step;
				line->y1 = (i + 1) * map->step;
				isometric_transform(&(line->x0), &(line->y0) , map->grid[i][j]);
				isometric_transform(&(line->x1), &(line->y1) , map->grid[i + 1][j]);
				dh = map->grid[i + 1][j] - map->grid[i][j];
				draw_line(mlx, line, colors, map, map->colors[i][j], map->grid[i][j], dh);
			}
			j++;
		}
		i++;
	}
}
 