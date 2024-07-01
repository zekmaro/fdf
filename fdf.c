/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 10:41:31 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
    if (!read_map(fd, vars.map, argv[1]))
	{
		free_map(vars.map);
		free_map_colors(vars.map);
		cleanup_vars(&vars);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	vars.map->rotation_x = 0;
	vars.map->rotation_y = 0;
	vars.map->rotation_z = 0;
	vars.map->step = calculate_step(&vars);
	get_max_height(vars.map);
	get_min_height(vars.map);
	calculate_center(vars.map);
    vars.mlx->mlx = mlx_init();
    vars.mlx->win = mlx_new_window(vars.mlx->mlx, vars.mlx->window_width, vars.mlx->window_height, "Draw Grid");
	get_data_image(vars.image, vars.mlx);
	draw_plane(vars.image, vars.line, vars.map, vars.colors);
	mlx_put_image_to_window(vars.mlx->mlx, vars.mlx->win, vars.image->mlx_img, 0, 0);
	mlx_key_hook(vars.mlx->win, key_hook, &vars);
	//mlx_hook(mlx.win, 17, 0, free_and_exit(&vars), &vars); // for escaping via button click
    mlx_loop(vars.mlx->mlx);
    return (0);
}

// REFACTOR THE CODE + FILE STRUCTURE (DONE (only left the white/red colors intialisation))
// GET RID OF LEAKS ( :) )
// IMPLEMENT ROTATIONS (WOKRING BUT I WANT TO CHANGE ROTATION AXES)
// DO GRADIENT (CURRENT FOCUS)