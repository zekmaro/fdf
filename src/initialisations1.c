/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:35:26 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 16:17:25 by anarama          ###   ########.fr       */
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
		free(colors);
		free(purple);
		free(red);
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

void	initialise_vars(t_vars *vars)
{
	initialise_image(vars);
	initialise_map(vars);
	initialise_colors(vars);
	initialise_mlx(vars);
	initialise_line(vars);
	vars->transform = isometric_transform;
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
