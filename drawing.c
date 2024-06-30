/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:44:22 by anarama           #+#    #+#             */
/*   Updated: 2024/06/30 20:04:18 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clean_screen(t_vars *vars)
{
	int x;
	int y;

	y = 0;	
	while (y != vars->mlx->window_height)
	{
		x = 0;
		while (x != vars->mlx->window_width)
		{
			put_pixel_to_image(vars->image, x, y, BLACK);
			x++;
		}
		y++;
	}
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

void draw_line(t_img *image, t_line *line, unsigned long color, t_colors *colors, t_map *map, int dh, int height)
{
	const int step_x = define_step(line->x0, line->x1);
	const int step_y = define_step(line->y0, line->y1);
	const int dx = abs(line->x1 - line->x0);
	const int dy = abs(line->y1 - line->y0);
	const int amount_pixels = sqrt(dx * dx + dy * dy);
	int fraction = amount_pixels / abs(dh);
	int error;
	int x0;
	int y0;
	
	int i = 0;
	error = 0;
	x0 = line->x0;
	y0 = line->y0;
	while (dh && fraction * abs(dh) < amount_pixels + amount_pixels / 4)
		fraction++;
	while (1)
	{
		color = calculate_gradient(colors->white, colors->red, map, height);
		put_pixel_to_image(image, x0, y0, color);
		if (i % fraction == 0)
		{
			if (dh > 0)
				height++;
			else if (dh < 0)
				height--;
		}
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

void	check_rotations(t_line *line, t_map *map, double angle_x, double angle_y, double angle_z)
{
	if (map->rotation_z != 0)
	{
		rotation_z(&line->x0, &line->y0, angle_z);
        rotation_z(&line->x1, &line->y1, angle_z);
	}
	if (map->rotation_x != 0)
	{
		rotation_x(&line->y0, &line->z0, angle_x);
		rotation_x(&line->y1, &line->z1, angle_x);
	}
	if (map->rotation_y != 0)
	{
		rotation_y(&line->x0, &line->z0, angle_y);
		rotation_y(&line->x1, &line->z1, angle_y);
	}
}

void	initialise_coordinates_x(t_line *line, t_map *map, int i, int j)
{
	line->x0 = j * map->step;
	line->y0 = i * map->step;
	line->z0 = map->grid[i][j];
	line->x1 = (j + 1) * map->step;
	line->y1 = i * map->step;
	line->z1 = map->grid[i][j + 1];
}

void	initialise_coordinates_y(t_line *line, t_map *map, int i, int j)
{
	line->x0 = j * map->step;
	line->y0 = i * map->step;
	line->z0 = map->grid[i][j];
	line->x1 = j * map->step;
	line->y1 = (i + 1) * map->step;
	line->z1 = map->grid[i + 1][j];
}

void	draw_plane(t_img *image, t_line *line, t_map *map, t_colors *colors)
{
	int i;
	int j;
	// better to put angles into their struct
	const double angle_z = map->rotation_z * (M_PI / 180.0);
	const double angle_x = map->rotation_x * (M_PI / 180.0);
	const double angle_y = map->rotation_y * (M_PI / 180.0);
	int dh;

	(void) colors;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (j < map->length - 1)
			{
				initialise_coordinates_x(line, map, i, j);
				check_rotations(line, map, angle_x, angle_y, angle_z);
				isometric_transform(&(line->x0), &(line->y0) , line->z0, line);
				isometric_transform(&(line->x1), &(line->y1) , line->z1, line);
				dh = map->grid[i][j + 1] - map->grid[i][j];
				draw_line(image, line, map->colors[i][j], colors, map, dh, map->grid[i][j]);
			}
			if (i < map->width - 1)
			{
				initialise_coordinates_y(line, map, i, j);
				check_rotations(line, map, angle_x, angle_y, angle_z);
				isometric_transform(&(line->x0), &(line->y0) , line->z0, line);
				isometric_transform(&(line->x1), &(line->y1) , line->z1, line);
				dh = map->grid[i + 1][j] - map->grid[i][j];
				draw_line(image, line, map->colors[i][j], colors, map, dh, map->grid[i][j]);
			}
			j++;
		}
		i++;
	}
}
 