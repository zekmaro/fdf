/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:27:25 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 15:01:37 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_min(const int num1, const int num2)
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
	const int	len1 = (vars->mlx->window_width - vars->line->x0) / 2;
	const int	len2 = (vars->mlx->window_height - vars->line->y0) / 2;

	return (ft_max(ft_min(len1 / vars->map->length,
				len2 / vars->map->width), 3));
}

void	calculate_center(t_map *map)
{
	map->center_x = map->length * map->step / 2;
	map->center_y = map->width * map->step / 2;
}
