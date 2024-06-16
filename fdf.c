/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/06/16 16:54:04 by anarama          ###   ########.fr       */
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

void	free_and_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
	mlx_destroy_display(vars->mlx->mlx);
	//mlx_destroy_image(vars->mlx->mlx, vars->image->addr);
	free(vars->mlx->mlx);
	ft_free_map(vars->map);
	ft_free_colors(vars->map);
	exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
    {
        ft_printf("Exiting program.\n");
		free_and_exit(vars);
    }
	else if (keycode == KEY_RIGHT)
	{
		ft_printf("Movind right.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->line->src_x += 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
	}
	else if (keycode == KEY_LEFT)
	{
		ft_printf("Movind left.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->line->src_x -= 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
	}
	else if (keycode == KEY_UP)
	{
		ft_printf("Movind right.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->line->src_y -= 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
	}
	else if (keycode == KEY_DOWN)
	{
		ft_printf("Movind left.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->line->src_y += 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
	}
	else if (keycode == KEY_PLUS)
	{
		ft_printf("Scaling up.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->map->step += 1;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
	}
	else if (keycode == KEY_MINUS)
	{
		ft_printf("Scaling down.\n");
		clean_screen(vars);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
		vars->map->step -= 1;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
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
	t_img image;

	int fd = 0;
	
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
	ft_bzero(&image, sizeof(t_img));
	
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
	vars.line = &line;
	vars.colors = &colors;
	
	line.src_x = 1000;
	line.src_y = 300;
	
	mlx.window_height = 1080;
	mlx.window_width = 1920;

	map.step = calculate_step(&line, mlx.window_width, mlx.window_height, &map); // can just pass &mlx
	
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, mlx.window_width, mlx.window_height, "Draw Grid");

	image.mlx_img = mlx_new_image(mlx.mlx, mlx.window_width, mlx.window_height);
	image.addr = mlx_get_data_addr(image.mlx_img, &(image.bits_per_pixel), &(image.line_len), &(image.endian));
	
	vars.image = &image;
	
	draw_plane(&image, &line, &map, &colors);

	mlx_put_image_to_window(mlx.mlx, mlx.win, image.mlx_img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &vars);
	//mlx_hook(mlx.win, 17, 0, free_and_exit(&vars), &vars);
    mlx_loop(mlx.mlx);
    return (0);
}


// calculate the center
// Refactor all the code and make it structure + nice
// Get rid of all leaks

// After we can start with rotations 
// And in the end do the gradient