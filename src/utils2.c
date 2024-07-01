/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:25:51 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 15:26:33 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_rotations(t_line *line, t_map *map, t_angles *angles)
{
	if (map->rotation_z != 0)
	{
		rotation_z(&line->x0, &line->y0, angles->angle_z);
        rotation_z(&line->x1, &line->y1, angles->angle_z);
	}
	if (map->rotation_x != 0)
	{
		rotation_x(&line->y0, &line->z0, angles->angle_x);
		rotation_x(&line->y1, &line->z1, angles->angle_x);
	}
	if (map->rotation_y != 0)
	{
		rotation_y(&line->x0, &line->z0, angles->angle_y);
		rotation_y(&line->x1, &line->z1, angles->angle_y);
	}
}

void	get_max_height(t_map *map)
{
	int i;
	int j;

	map->max_height = map->grid[0][0];
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->max_height < map->grid[i][j])
				map->max_height = map->grid[i][j];
			j++;
		}
		i++;
	}
}

void	get_min_height(t_map *map)
{
	int i;
	int j;

	map->min_height = map->grid[0][0];
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->min_height > map->grid[i][j])
				map->min_height = map->grid[i][j];
			j++;
		}
		i++;
	}
}
void	scale_heights_up(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->width - 1)
	{
		j = 0;
		while (j < map->length - 1)
		{
			if (map->grid[i][j] != 0)
			{
				map->grid[i][j] += 10;
				if (map->grid[i][j] == 0)
					map->grid[i][j] += 10;
			}
			j++;
		}
		i++;
	}
}

void	scale_heights_down(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->width - 1)
	{
		j = 0;
		while (j < map->length - 1)
		{
			if (map->grid[i][j] != 0)
			{
				map->grid[i][j] -= 10;
				if (map->grid[i][j] == 0)
					map->grid[i][j] -= 10;
			}
			j++;
		}
		i++;
	}
}
