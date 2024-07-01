/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:35:26 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 15:34:04 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_colors(t_vars *vars)
{
	t_color		*purple;
	t_color		*red;
	t_colors	*colors;

	colors = (t_colors *)(malloc(sizeof(t_colors)));
	purple = (t_color *)(malloc(sizeof(t_color)));
	red = (t_color *)(malloc(sizeof(t_color)));
	if (!colors || !purple || !red)
	{
		cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(colors, sizeof(t_colors));
	ft_bzero(purple, sizeof(t_color));
	ft_bzero(red, sizeof(t_color));
	purple->color = PURPLE;
	red->color = RED;
	initialise_rgb(purple);
	initialise_rgb(red);
	colors->top = red;
	colors->low = purple;
	vars->colors = colors;
}

void	initialise_mlx(t_vars *vars)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
	{
		cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->window_height = 1080;
	mlx->window_width = 1920;
	vars->mlx = mlx;
}

void	initialise_line(t_vars *vars)
{
	t_line	*line;

	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
	{
		cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(line, sizeof(t_line));
	line->src_x = 1000;
	line->src_y = 300;
	vars->line = line;
}

void	initialise_image(t_vars *vars)
{
	t_img	*image;
	
	image = (t_img *)(malloc(sizeof(t_img)));
	if (!image)
	{
		cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(image, sizeof(t_img));
	vars->image = image;
}

void	initialise_map(t_vars *vars)
{
	t_map	*map;

	map = (t_map *)(malloc(sizeof(t_map)));
	if (!map)
	{
		cleanup_vars(vars);
		exit (1);
	}
	ft_bzero(map, sizeof(t_map));
	calculate_center(map);
	vars->map = map;
}

void	initialise_vars(t_vars *vars)
{
	initialise_image(vars);
	initialise_map(vars);
	initialise_colors(vars);
	initialise_mlx(vars);
	initialise_line(vars);
}

void	initialise_map_vars(t_vars *vars)
{
	vars->map->rotation_x = 0;
	vars->map->rotation_y = 0;
	vars->map->rotation_z = 0;
	vars->map->step = calculate_step(vars);
	get_max_height(vars->map);
	get_min_height(vars->map);
	calculate_center(vars->map);
}

void	inititalise_angles(t_angles *angles, t_vars *vars)
{
	angles->angle_x = vars->map->rotation_x * (M_PI / 180.0);
	angles->angle_y = vars->map->rotation_y * (M_PI / 180.0);
	angles->angle_z = vars->map->rotation_z * (M_PI / 180.0);
}
