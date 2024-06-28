/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 12:31:15 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_center(t_map *map)
{
	map->center_x = map->length / 2;
	map->center_y = map->width / 2;
}

void rotate_up(t_map *map)
{
	int i;
	int j;
	int height_change = 1;
	
	i = 0;
	while (i < map->center_y)
	{
		j = 0;
		while (j < map->length)
		{
			map->grid[i][j] += (height_change * (map->center_y - i));
			map->grid[map->width - i - 1][map->length - j - 1] -= (height_change * (map->center_y - i));
			j++;
		}
		i++;
	}
	ft_print_map(map);
}

void rotate_down(t_map *map)
{
	int i;
	int j;
	int height_change = 1;
	
	i = 0;
	while (i < map->center_y)
	{
		j = 0;
		while (j < map->length)
		{
			map->grid[i][j] -= (height_change * (map->center_y - i));
			map->grid[map->width - i - 1][map->length - j - 1] += (height_change * (map->center_y - i));
			j++;
		}
		i++;
	}
	ft_print_map(map);
}

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


void cleanup_vars(t_vars *vars) 
{
    if (vars->map) free(vars->map);
    if (vars->image) free(vars->image);
    if (vars->colors) free(vars->colors);
    if (vars->mlx) free(vars->mlx);
    if (vars->line) free(vars->line);
	exit (1);
}

// Handle freeing correctly
void	free_and_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
	//mlx_destroy_display(vars->mlx->mlx);
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
		vars->line->src_x += 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == KEY_LEFT)
	{
		ft_printf("Movind left.\n");
		clean_screen(vars);
		vars->line->src_x -= 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == KEY_UP)
	{
		ft_printf("Movind right.\n");
		clean_screen(vars);
		vars->line->src_y -= 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == KEY_DOWN)
	{
		ft_printf("Movind left.\n");
		clean_screen(vars);
		vars->line->src_y += 20;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == KEY_PLUS)
	{
		ft_printf("Scaling up.\n");
		clean_screen(vars);
		vars->map->step += 1;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == KEY_MINUS)
	{
		ft_printf("Scaling down.\n");
		clean_screen(vars);
		vars->map->step -= 1;
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == W)
	{
		ft_printf("Rotating up.\n");
		clean_screen(vars);
		//rotate_up(vars->map);
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	}
	else if (keycode == S)
	{
		ft_printf("Rotating down.\n");
		clean_screen(vars);
		//rotate_down(vars->map);
		draw_plane(vars->image, vars->line, vars->map, vars->colors);
		mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
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

void	initialise_vars(t_vars *vars)
{
	t_img		*image;
	t_colors	*colors;
	t_mlx		*mlx;
	t_line		*line;
	t_map		*map;

	map = (t_map *)(malloc(sizeof(t_map)));
	if (!map)
		cleanup_vars(vars);
	ft_bzero(map, sizeof(t_map));
	calculate_center(map);
	vars->map = map;

	image = (t_img *)(malloc(sizeof(t_img)));
	if (!image)
		cleanup_vars(vars);
	ft_bzero(image, sizeof(t_img));
	vars->image = image;

	colors = (t_colors *)(malloc(sizeof(t_colors)));
	if (!colors)
		cleanup_vars(vars);
	ft_bzero(colors, sizeof(t_colors));
	initialise_colors(colors);
	vars->colors = colors;

	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
		cleanup_vars(vars);
	ft_bzero(mlx, sizeof(t_mlx));
	initialise_mlx(mlx);
	vars->mlx = mlx;

	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
		cleanup_vars(vars);
	ft_bzero(line, sizeof(t_line));
	initialise_line(line);
	vars->line = line;
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	fd = 0;
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
	ft_bzero(&vars, sizeof(t_vars));
	initialise_vars(&vars);
	ft_printf("pointer in main %p\n", vars.map);
    if (!read_map(fd, vars.map, argv[1]))
	{
		ft_free_map(vars.map);
		ft_free_colors(vars.map);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	ft_printf("pointer in main %p\n", vars.map);
	ft_printf("check %d\n", vars.map->width);
	ft_print_map(vars.map);
	// Works DONT TOUCH
	vars.map->step = calculate_step(&vars);
    vars.mlx->mlx = mlx_init();
    vars.mlx->win = mlx_new_window(vars.mlx->mlx, vars.mlx->window_width, vars.mlx->window_height, "Draw Grid");
	initialise_image(vars.image, vars.mlx);
	draw_plane(vars.image, vars.line, vars.map, vars.colors);
	mlx_put_image_to_window(vars.mlx->mlx, vars.mlx->win, vars.image->mlx_img, 0, 0);
	mlx_key_hook(vars.mlx->win, key_hook, &vars);
	//mlx_hook(mlx.win, 17, 0, free_and_exit(&vars), &vars);
    mlx_loop(vars.mlx->mlx);
    return (0);
}

// Need to implement double pointers
// Before duing rotations i need to refactor the code. its impossible to work with
// Get rid of all leaks

// After we can start with rotations 
// And in the end do the gradient