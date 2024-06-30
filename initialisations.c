/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:44:35 by andrejarama       #+#    #+#             */
/*   Updated: 2024/06/30 17:28:35 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_colors(t_vars *vars, t_colors *colors)
{
	t_color *white;
	t_color *red;

	colors = (t_colors *)(malloc(sizeof(t_colors)));
	white = (t_color *)(malloc(sizeof(t_color)));
	red = (t_color *)(malloc(sizeof(t_color)));
	if (!colors || !white || !red)
		cleanup_vars(vars);
	ft_bzero(colors, sizeof(t_colors));
	ft_bzero(white, sizeof(t_color));
	ft_bzero(red, sizeof(t_color));
	white->color = WHITE;
	red->color = RED;
	colors->red = red;
	colors->white = white;
	initialise_rgb(colors->white);
	initialise_rgb(colors->red);
	vars->colors = colors;
}

void	initialise_mlx(t_vars *vars, t_mlx *mlx)
{
	mlx = (t_mlx *)(malloc(sizeof(t_mlx)));
	if (!mlx)
		cleanup_vars(vars);
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->window_height = 1080;
	mlx->window_width = 1920;
	vars->mlx = mlx;
}

void	initialise_line(t_vars *vars, t_line *line)
{
	line = (t_line *)(malloc(sizeof(t_line)));
	if (!line)
		cleanup_vars(vars);
	ft_bzero(line, sizeof(t_line));
	line->src_x = 1000;
	line->src_y = 300;
	vars->line = line;
}

void	initialise_image(t_vars *vars, t_img *image)
{
	image = (t_img *)(malloc(sizeof(t_img)));
	if (!image)
		cleanup_vars(vars);
	ft_bzero(image, sizeof(t_img));
	vars->image = image;
}

void	initialise_map(t_vars *vars, t_map *map)
{
	map = (t_map *)(malloc(sizeof(t_map)));
	if (!map)
		cleanup_vars(vars);
	ft_bzero(map, sizeof(t_map));
	calculate_center(map);
	vars->map = map;
}

void	initialise_vars(t_vars *vars)
{
	t_img		*image;
	t_colors	*colors;
	t_mlx		*mlx;
	t_line		*line;
	t_map		*map;

	image = NULL;
	colors = NULL;
	mlx = NULL;
	line = NULL;
	map = NULL;

	initialise_image(vars, image);
	initialise_map(vars, map);
	initialise_colors(vars, colors);
	initialise_mlx(vars, mlx);
	initialise_line(vars, line);
}
