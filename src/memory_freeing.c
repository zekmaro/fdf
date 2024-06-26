/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_freeing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:44:48 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 15:34:59 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    free_memory(char **arr)
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

void    free_map(t_map *map)
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

void    free_map_colors(t_map *map)
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
    if (vars->map) 
	{
        free_map_colors(vars->map);
        free_map(vars->map);
        free(vars->map);
    }
    if (vars->image) 
	{
        if (vars->image->mlx_img)
            mlx_destroy_image(vars->mlx->mlx, vars->image->mlx_img);
        free(vars->image);
    }
    if (vars->colors) 
	{
        if (vars->colors->low)
			free(vars->colors->low);
        if (vars->colors->top) 
			free(vars->colors->top);
        free(vars->colors);
    }
    if (vars->mlx) 
	{
        if (vars->mlx->win)
            mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
        if (vars->mlx->mlx) 
		{
            mlx_destroy_display(vars->mlx->mlx);
            free(vars->mlx->mlx); // This frees the display structure
        }
        free(vars->mlx);
    }
    if (vars->line) 
		free(vars->line);
}


// Handle freeing correctly
void	free_and_exit(t_vars *vars)
{
	cleanup_vars(vars);
	exit(0);
}
