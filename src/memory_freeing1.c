/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_freeing1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:44:48 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 14:50:41 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_memory(char **arr)
{
	char	**temp;

	temp = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(temp);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	free_map_colors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		free(map->colors[i]);
		i++;
	}
	free(map->colors);
}

void	free_and_exit(t_vars *vars)
{
	cleanup_vars(vars);
	exit(0);
}
