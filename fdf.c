/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/31 16:06:34 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_hook(int keycode, t_vars *vars)
{
    if (keycode == ESCAPE)
    {
        printf("Exiting program.\n");
        if (vars->mlx->win)
		{
			mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
			mlx_destroy_display(vars->mlx->mlx);
			free(vars->mlx->mlx);
		}
		ft_free_map(vars->map);
		ft_free_colors(vars->map);
		exit(0);
    }
	return (0);
}

int main(int argc, char **argv)
{
    int fd;
    t_map map;
	t_mlx mlx;
	t_line line;
	t_vars vars;
	int window_width;
	int	window_height;
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
	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&line, sizeof(line));
	ft_bzero(&vars, sizeof(vars));
    if (!read_map(fd, &map, argv[1]))
	{
		ft_free_map(&map);
		ft_free_colors(&map);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	vars.map = &map;
	vars.mlx = &mlx;

	line.x0 = 800;
	line.y0 = 100;
	window_height = 1080;
	window_width = 1920;

	step = calculate_step(&line, window_width, window_height, &map);	
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "Draw Grid");
	draw_plane(&mlx, &line, &map, step);
	mlx_key_hook(mlx.win, key_hook, &vars);
    mlx_loop(mlx.mlx);
    return (0);
}

// Leaking one byte probably because of GNL somewhere
// DRAW LINE 
// DRAW PLANE 
// How to calculate step? done but later do hot keys on zooming and movind
// ADD COLORS done
// DRAW PLANE WITH COLORS done
// BUTTON FOR EXIT
// DRAW PLANE WITH HEIGHTS
