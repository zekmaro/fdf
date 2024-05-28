/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/28 22:47:12 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void isometric_transform(int *x, int *y, int origin_x, int origin_y)
{
    int temp_x = *x - origin_x;
    int temp_y = *y - origin_y;

    int iso_x;
    int iso_y;
    double angle = M_PI / 6; // 30 degrees in radians

    iso_x = temp_x * cos(angle) - temp_y * sin(angle);
    iso_y = temp_x * sin(angle) + temp_y * cos(angle);

    *x = iso_x + origin_x;
    *y = iso_y + origin_y;
}

void draw_line(t_mlx *mlx, t_line *line, int color)
{
	int dx;
	int dy;
	int step_x;
	int step_y;
	int error;
	int x1;
	int y1;

	dx = abs(line->x1 - line->x0);
	dy = abs(line->y1 - line->y0);
	error = 0;
	step_x = 0;
	step_y = 0;
	if (line->x0 < line->x1)
		step_x = 1;
	else if (line->x0 > line->x1)
		step_x = -1;
	if (line->y0 < line->y1)
		step_y = 1;
	else if (line->y0 > line->y1)
		step_y = -1;
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

void	draw_plane(t_mlx *mlx, t_line *line, t_map *map, int color, int step)
{
	int save_x;
	int save_y;
	int i;
	int j;
	int	src_x;
	int src_y;

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
			if (j != map->length)
				draw_line(mlx, line, color);
			line->x1 = line->x0;
			line->y1 = line->y0 + step;
			isometric_transform(&(line->x1), &(line->y1), line->x0, line->y0);
			if (i != map->width)
				draw_line(mlx, line, color);
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
		if (i != map->width)
			draw_line(mlx, line, color);
		line->x0 = line->x1;
		line->y0 = line->y1;
		i++;
	}
}

int main(int argc, char **argv)
{
    int fd;
    t_map map;

    if (argc != 2)
    {
        perror("Usage: ./fdf <filename>\n");
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Invalid file descriptor!\n");
        exit(EXIT_FAILURE);
    }
    ft_bzero(&map, sizeof(t_map));
    if (!read_map(fd, &map, argv[1]))
	{
		ft_free_map(&map);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	// ft_print_map(&map);

	
	t_mlx mlx;  // Initialize MLX structure
	t_line line;
	int step;

	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&line, sizeof(line));
	
	line.x0 = 300;
	line.y0 = 200;
	// line.x1 = 111;
	// line.y1 = 666;
	step = 50;
	
    mlx.mlx = mlx_init();  // Initialize MiniLibX
    mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "Draw Grid");
	draw_plane(&mlx, &line, &map, 0xFFFFFF, step);
	// draw_line(&mlx, &line, 0xFFFFFF);
	mlx_loop(mlx.mlx);
    ft_free_map(&map);
    return (0);
}

// Leaking one byte probably because of GNL somewhere
// DRAW LINE 
// DRAW PLANE 
// ADD COLORS
// DRAW PLANE WITH COLORS
