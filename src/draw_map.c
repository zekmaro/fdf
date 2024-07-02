/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:14:55 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 21:30:56 by andrejarama      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_coordinates_x(t_line *line, t_map *map, int i, int j)
{
	line->x0 = j * map->step;
	line->y0 = i * map->step;
	line->z0 = map->grid[i][j];
	line->x1 = (j + 1) * map->step;
	line->y1 = i * map->step;
	line->z1 = map->grid[i][j + 1];
}

void	initialise_coordinates_y(t_line *line, t_map *map, int i, int j)
{
	line->x0 = j * map->step;
	line->y0 = i * map->step;
	line->z0 = map->grid[i][j];
	line->x1 = j * map->step;
	line->y1 = (i + 1) * map->step;
	line->z1 = map->grid[i + 1][j];
}

void	get_coor_data_x(t_vars *vars, t_angles *angles, int i, int j)
{
	initialise_coordinates_x(vars->line, vars->map, i, j);
	check_rotations(vars->line, vars->map, angles);
	isometric_transform(&(vars->line->x0), &(vars->line->y0) , vars->line->z0, vars->line);
	isometric_transform(&(vars->line->x1), &(vars->line->y1) , vars->line->z1, vars->line);
	vars->line->dh = vars->map->grid[i][j + 1] - vars->map->grid[i][j];
}

void	get_coor_data_y(t_vars *vars, t_angles *angles, int i, int j)
{
	initialise_coordinates_y(vars->line, vars->map, i, j);
	check_rotations(vars->line, vars->map, angles);
	isometric_transform(&(vars->line->x0), &(vars->line->y0) , vars->line->z0, vars->line);
	isometric_transform(&(vars->line->x1), &(vars->line->y1) , vars->line->z1, vars->line);
	vars->line->dh = vars->map->grid[i + 1][j] - vars->map->grid[i][j];
}

void	draw_map(t_vars *vars)
{
	int 		i;
	int 		j;
	t_angles	angles;

	inititalise_angles(&angles, vars);
	i = 0;
	while (i < vars->map->width)
	{
		j = 0;
		while (j < vars->map->length)
		{
			if (j < vars->map->length - 1)
			{
				get_coor_data_x(vars, &angles, i, j);
				draw_line(vars, vars->map->colors[i][j], vars->map->grid[i][j]);
			}
			if (i < vars->map->width - 1)
			{
				get_coor_data_y(vars, &angles, i, j);
				draw_line(vars, vars->map->colors[i][j], vars->map->grid[i][j]);
			}
			j++;
		}
		i++;
	}
}
