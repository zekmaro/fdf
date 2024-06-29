/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/28 20:10:43 by andrejarama      ###   ########.fr       */
=======
/*   Updated: 2024/06/28 15:28:49 by anarama          ###   ########.fr       */
>>>>>>> 8a8b299 (some change in fdf.c)
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_key(int keycode, t_vars *vars)
{
	if (keycode == KEY_RIGHT)
		vars->line->src_x += 20;
	else if (keycode == KEY_LEFT)
		vars->line->src_x -= 20;
	else if (keycode == KEY_UP)
		vars->line->src_y -= 20;
	else if (keycode == KEY_DOWN)
		vars->line->src_y += 20;
	else if (keycode == KEY_PLUS)
		vars->map->step += 1;
	else if (keycode == KEY_MINUS)
		vars->map->step -= 1;
	else if (keycode == W)
	{
		//rotate_up(vars->map);
	}
	else if (keycode == S)
	{
		//rotate_down(vars->map);
	}
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
    {
        ft_printf("Exiting program.\n");
		free_and_exit(vars);
    }
	clean_screen(vars);
	handle_key(keycode, vars);
	draw_plane(vars->image, vars->line, vars->map, vars->colors);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	return (0);
}

void	get_data_image(t_img *image, t_mlx *mlx)
{
	image->mlx_img = mlx_new_image(mlx->mlx, mlx->window_width, mlx->window_height);
	image->addr = mlx_get_data_addr(image->mlx_img, &(image->bits_per_pixel), &(image->line_len), &(image->endian));
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
		free_map(vars.map);
		free_map_colors(vars.map);
		cleanup_vars(&vars);
        perror("Error reading line!\n");
        exit(EXIT_FAILURE);
	}
	// Works DONT TOUCH
	vars.map->step = calculate_step(&vars);
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
// IMPLEMENT ROTATIONS (CURRENT FOCUS)
// DO GRADIENT