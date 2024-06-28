/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:44:22 by anarama           #+#    #+#             */
/*   Updated: 2024/06/21 22:59:11 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void put_pixel_to_image(t_img *image, int x, int y, int color)
{
    int index;

    index = (x * (image->bits_per_pixel / 8)) + (y * (image->line_len));
    (image->addr)[index] = color & 0xFF;
    (image->addr)[index + 1] = (color >> 8) & 0xFF;
    (image->addr)[index + 2] = (color >> 16) & 0xFF;
}

void rotation_up_transform(int *x, int *y, int dx, int dy)
{
	*x -= dx;
	*y -= dy;
}

void isometric_transform(int *x, int *y, int z, t_line *line)
{
    const double angle = M_PI / 6;
   	int temp_x = *x;
    int temp_y = *y;
	*x = (temp_x - temp_y) * cos(angle) + line->src_x;
	*y = (temp_x + temp_y) * sin(angle) - z + line->src_y;
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
 