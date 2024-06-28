/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:27:25 by anarama           #+#    #+#             */
/*   Updated: 2024/06/23 00:50:23 by andrejarama      ###   ########.fr       */
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

void ft_print_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->width)
    {
        j = 0;
        while (j < map->length)
        {
            ft_printf("%d ", map->grid[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

void print_colors(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->width)
    {
        j = 0;
        while (j < map->length)
        {
            printf("%lu", map->colors[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

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