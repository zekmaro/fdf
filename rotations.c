/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:04:42 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 14:05:07 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotate_up(t_map *map)
{
	int i;
	int j;
	int height_change = 1;
	
	i = 0;
	while (i < map->center_y)
	{
		j = 0;
		while (j < map->length)
		{
			map->grid[i][j] += (height_change * (map->center_y - i));
			map->grid[map->width - i - 1][map->length - j - 1] -= (height_change * (map->center_y - i));
			j++;
		}
		i++;
	}
	ft_print_map(map);
}

void rotate_down(t_map *map)
{
	int i;
	int j;
	int height_change = 1;
	
	i = 0;
	while (i < map->center_y)
	{
		j = 0;
		while (j < map->length)
		{
			map->grid[i][j] -= (height_change * (map->center_y - i));
			map->grid[map->width - i - 1][map->length - j - 1] += (height_change * (map->center_y - i));
			j++;
		}
		i++;
	}
	ft_print_map(map);
}