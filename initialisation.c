/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:44:35 by andrejarama       #+#    #+#             */
/*   Updated: 2024/06/23 00:31:41 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_colors(t_colors *colors)
{
	t_color white;
	t_color red;
	
	ft_bzero(&white, sizeof(t_color));
	ft_bzero(&red, sizeof(t_color));
	white.color = WHITE;
	red.color = RED;
	colors->red = &red;
	colors->white = &white;
	initialise_rgb(colors->white);
	initialise_rgb(colors->red);
}

void	initialise_mlx(t_mlx *mlx)
{
	mlx->window_height = 1080;
	mlx->window_width = 1920;
}

void	initialise_line(t_line *line)
{
	line->src_x = 1000;
	line->src_y = 300;
}

void	initialise_image(t_img *image, t_mlx *mlx)
{
	image->mlx_img = mlx_new_image(mlx->mlx, mlx->window_width, mlx->window_height);
	image->addr = mlx_get_data_addr(image->mlx_img, &(image->bits_per_pixel), &(image->line_len), &(image->endian));
}