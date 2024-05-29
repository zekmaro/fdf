/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/29 18:18:17 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    int fd;
    t_map map;
	int window_width;
	int	window_height;
	t_mlx mlx;
	t_line line;
	int step;

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
	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&line, sizeof(line));
	
	line.x0 = 800;
	line.y0 = 100;
	window_height = 1080;
	window_width = 1920;
	// line.x1 = 111;
	// line.y1 = 666;
	step = calculate_step(&line, window_width, window_height, &map);	
    mlx.mlx = mlx_init();  // Initialize MiniLibX
    mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "Draw Grid");
	draw_plane(&mlx, &line, &map, 0xFFFFFF, step);
	// draw_line(&mlx, &line, 0xFFFFFF);
	mlx_loop(mlx.mlx);
    ft_free_map(&map);
    return (0);
}

// Leaking one byte probably because of GNL somewhere
// DRAW LINE 
// DRAW PLANE 
// How to calculate step? dome but later do hot keys on zooming and movind
// ADD COLORS
// DRAW PLANE WITH COLORS
