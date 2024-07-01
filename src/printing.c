/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:43:09 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 12:44:05 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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