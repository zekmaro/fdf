/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:40:18 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 14:45:04 by anarama          ###   ########.fr       */
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
			put_pixel_to_image(vars, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	get_data_image(t_img *image, t_mlx *mlx)
{
	image->mlx_img = mlx_new_image(mlx->mlx, mlx->window_width, mlx->window_height);
	image->addr = mlx_get_data_addr(image->mlx_img, &(image->bits_per_pixel), &(image->line_len), &(image->endian));
}

void put_pixel_to_image(t_vars *vars, int x, int y, int color)
{
    int index;

	if (x >= 0 && x < vars->mlx->window_width && y >= 0 && y < vars->mlx->window_height)
	{
		index = (x * (vars->image->bits_per_pixel / 8)) + (y * (vars->image->line_len));
    	(vars->image->addr)[index] = color & 0xFF;
    	(vars->image->addr)[index + 1] = (color >> 8) & 0xFF;
    	(vars->image->addr)[index + 2] = (color >> 16) & 0xFF;
	}
}
