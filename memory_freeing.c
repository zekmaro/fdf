/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_freeing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:44:48 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 14:48:39 by anarama          ###   ########.fr       */
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

void ft_free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->width)
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
}

void ft_free_colors(t_map *map)
{
    int i;

    i = 0;
    while (i < map->width)
    {
        free(map->colors[i]);
        i++;
    }
    free(map->colors);
}

void cleanup_vars(t_vars *vars) 
{
    if (vars->map) free(vars->map);
    if (vars->image) free(vars->image);
    if (vars->colors) free(vars->colors);
    if (vars->mlx) free(vars->mlx);
    if (vars->line) free(vars->line);
	exit (1);
}

// Handle freeing correctly
void	free_and_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
	//mlx_destroy_display(vars->mlx->mlx);
	//mlx_destroy_image(vars->mlx->mlx, vars->image->addr);
	free(vars->mlx->mlx);
	ft_free_map(vars->map);
	ft_free_colors(vars->map);
	exit(0);
}
