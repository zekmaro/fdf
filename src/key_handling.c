/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:34:50 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 17:33:17 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_translation(int keycode, t_vars *vars)
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
}

void	check_rotation(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->map->rotation_x += 10;
	else if (keycode == S)
		vars->map->rotation_x -= 10;
	else if (keycode == Q)
		vars->map->rotation_z += 10;
	else if (keycode == E)
		vars->map->rotation_z -= 10;
	else if (keycode == A)
		vars->map->rotation_y += 10;
	else if (keycode == D)
		vars->map->rotation_y -= 10;
}

void	check_scaling(int keycode, t_vars *vars)
{
	if (keycode == SCALE_HEIGHTS_UP)
	{
		scale_heights_up(vars->map);
		get_max_height(vars->map);
		get_min_height(vars->map);
	}
	else if (keycode == SCALE_HEIGHTS_DOWN)
	{
		scale_heights_down(vars->map);
		get_max_height(vars->map);
		get_min_height(vars->map);
	}
}

void	handle_key(int keycode, t_vars *vars)
{
	check_translation(keycode, vars);
	check_rotation(keycode, vars);
	check_scaling(keycode, vars);
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
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx->mlx, vars->mlx->win, vars->image->mlx_img, 0, 0);
	return (0);
}
