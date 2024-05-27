/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/27 19:07:21 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void isometric_transform(int *x, int *y)
{
    int iso_x;
    int iso_y;
    double angle = M_PI / 6; // 30 degrees in radians

    iso_x = (*x - *y) * cos(angle);
    iso_y = (*x + *y) * sin(angle);

    *x = iso_x;
    *y = iso_y;
}

void draw_line(t_mlx *mlx, t_line *line, int color)
{
	int dx;
	int dy;
	int step_x;
	int step_y;

	dx = abs(line->x1 - line->x0);
	dy = abs(line->y1 - line->y0);
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
	while (1)
	{
		mlx_pixel_put(mlx->mlx, mlx->win, line->x0, line->y0 , color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		line->x0 += step_x;
		line->y0 += step_y;
	}
}

void	draw_plane(t_mlx *mlx, t_line *line, t_map *map, int color, int step)
{
	int dest_x;
	int dest_y;
	int source_x;
	int source_y;
	int save;
	
	dest_x = line->x0 + step * map->length;
	dest_y = line->y0 + step * map->width;
	source_y = line->y0;
	save = line->x0;
	while (source_y <= dest_y)
	{
		source_x = save;
		while (source_x <= dest_x)
		{
			line->x0 = source_x;
			line->y0 = source_y;
			line->y1 = source_y + step;
			line->x1 = source_x;
			draw_line(mlx, line, color);
			line->x0 = source_x;
			line->y0 = source_y;
			line->y1 = source_y;
			line->x1 = source_x + step;
			draw_line(mlx, line, color);
			source_x += step;
		}
		source_y += step;
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
	ft_print_map(&map);

	
	t_mlx mlx;  // Initialize MLX structure
	t_line line;
	int step;

	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&line, sizeof(line));
	
	line.x0 = 100;
	line.y0 = 100;
	step = 20;
	
    mlx.mlx = mlx_init();  // Initialize MiniLibX
    mlx.win = mlx_new_window(mlx.mlx, 800, 600, "Draw Grid");
	draw_plane(&mlx, &line, &map, 0xFFFFFF, step);

	mlx_loop(mlx.mlx);
    ft_free_map(&map);
    return (0);
}

// Leaking one byte probably because of GNL somewhere
// DRAW LINE 
// DRAW PLANE 
// ADD COLORS
// DRAW PLANE WITH COLORS
