/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:27:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/27 14:27:52 by anarama          ###   ########.fr       */
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