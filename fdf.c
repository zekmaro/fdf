/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/06/11 18:54:39 by anarama          ###   ########.fr       */
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

void	get_max_height(t_map *map)
{
	int i;
	int j;

	map->max_height = map->grid[0][0];
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->max_height < map->grid[i][j])
				map->max_height = map->grid[i][j];
			j++;
		}
		i++;
	}
}

void	get_min_height(t_map *map)
{
	int i;
	int j;

	map->min_height = map->grid[0][0];
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->min_height > map->grid[i][j])
				map->min_height = map->grid[i][j];
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
    t_map map;
	t_mlx mlx;
	t_line line;
	t_vars vars;
	t_color white;
	t_color red;
	t_colors colors;

	int fd;
	int window_width;
	int	window_height;
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
	ft_bzero(&mlx, sizeof(t_mlx));
	ft_bzero(&line, sizeof(t_line));
	ft_bzero(&vars, sizeof(t_vars));
	ft_bzero(&white, sizeof(t_color));
	ft_bzero(&red, sizeof(t_color));
	ft_bzero(&colors, sizeof(t_colors));
    if (!read_map(fd, &map, argv[1]))
	{
		ft_free_map(&map);
		ft_free_colors(&map);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	white.color = WHITE;
	red.color = RED;
	colors.white = &white;
	colors.red = &red;
	
	initialise_rgb(&white);
	initialise_rgb(&red);

	get_max_height(&map);
	get_min_height(&map);

	vars.map = &map;
	vars.mlx = &mlx;
	line.x0 = 800;
	line.y0 = 100;
	window_height = 1080;
	window_width = 1920;

	map.step = calculate_step(&line, window_width, window_height, &map);	
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "Draw Grid");
	draw_plane(&mlx, &line, &map, &colors);
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
