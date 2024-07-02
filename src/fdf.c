/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 21:51:28 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void run_screen(t_vars *vars)
{
    vars->mlx->mlx = mlx_init();
    if (!vars->mlx->mlx) 
	{
        free_and_exit(vars);
	}
    vars->mlx->win = mlx_new_window(vars->mlx->mlx, vars->mlx->window_width, vars->mlx->window_height, "Draw Grid");
    if (!vars->mlx->win) 
	{
        free_and_exit(vars);
    }
    get_data_image(vars->image, vars->mlx);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
    mlx_key_hook(vars->mlx->win, key_hook, vars);
    mlx_hook(vars->mlx->win, 17, 0, (int (*)(void))free_and_exit, vars);
    mlx_loop(vars->mlx->mlx);
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
    if (!read_map(fd, vars.map, argv[1]))
	{
		cleanup_vars(&vars);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	initialise_map_vars(&vars);
	run_screen(&vars);
    return (0);
}

// Differ between colors and gradient?