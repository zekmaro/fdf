/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:27:25 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 14:04:16 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_min(const int num1, const int num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

int	ft_max(const int num1, const int num2)
{
	if (num1 < num2)
		return (num2);
	return (num1);
}

int	calculate_step(t_vars *vars)
{
	const int len1 = (vars->mlx->window_width - vars->line->x0) / 2;
	const int len2 = (vars->mlx->window_height - vars->line->y0) / 2;
	return (ft_max(ft_min(len1 / vars->map->length, len2 / vars->map->width), 3));
}

void	calculate_center(t_map *map)
{
	map->center_x = map->length / 2;
	map->center_y = map->width / 2;
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
