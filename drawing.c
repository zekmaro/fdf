/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:44:22 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 14:05:20 by anarama          ###   ########.fr       */
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
	ft_printf("im done\n");
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

void draw_line(t_img *image, t_line *line, unsigned long color)
{
	const int step_x = define_step(line->x0, line->x1);
	const int step_y = define_step(line->y0, line->y1);
	const int dx = abs(line->x1 - line->x0);
	const int dy = abs(line->y1 - line->y0);
	int error;
	int x0;
	int y0;

	int i = 0;
	error = 0;
	x0 = line->x0;
	y0 = line->y0;
	while (1)
	{
		put_pixel_to_image(image, x0, y0, color);
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

void	draw_plane(t_img *image, t_line *line, t_map *map, t_colors *colors)
{
	int i;
	int j;
	//int dh;
	
	(void) colors;
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
				isometric_transform(&(line->x0), &(line->y0) , map->grid[i][j], line);
				isometric_transform(&(line->x1), &(line->y1) , map->grid[i][j + 1], line);
				draw_line(image, line, map->colors[i][j]);
			}
			if (i < map->width - 1)
			{
				line->x0 = j * map->step;
				line->y0 = i * map->step;
				line->x1 = j * map->step;
				line->y1 = (i + 1) * map->step;
				isometric_transform(&(line->x0), &(line->y0) , map->grid[i][j], line);
				isometric_transform(&(line->x1), &(line->y1) , map->grid[i + 1][j], line);
				//dh = map->grid[i + 1][j] - map->grid[i][j];
				draw_line(image, line, map->colors[i][j]);
			}
			j++;
		}
		i++;
	}
	ft_printf("I drew a plane\n");
}
 