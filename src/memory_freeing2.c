/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_freeing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:43:42 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 14:54:06 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_vars_map(t_vars *vars)
{
	if (vars->map->colors)
		free_map_colors(vars->map);
	if (vars->map->grid)
		free_map(vars->map);
	free(vars->map);
}

void	free_vars_image(t_vars *vars)
{
	if (vars->image->mlx_img)
		mlx_destroy_image(vars->mlx->mlx, vars->image->mlx_img);
	free(vars->image);
}

void	free_vars_colors(t_vars *vars)
{
	if (vars->colors->low)
		free(vars->colors->low);
	if (vars->colors->top)
		free(vars->colors->top);
	free(vars->colors);
}

void	free_vars_mlx(t_vars *vars)
{
	if (vars->mlx->win)
		mlx_destroy_window(vars->mlx->mlx, vars->mlx->win);
	if (vars->mlx->mlx)
	{
		mlx_destroy_display(vars->mlx->mlx);
		free(vars->mlx->mlx);
	}
	free(vars->mlx);
}

void	cleanup_vars(t_vars *vars)
{
	if (vars->map)
	{
		free_vars_map(vars);
	}
	if (vars->image)
	{
		free_vars_image(vars);
	}
	if (vars->colors)
	{
		free_vars_colors(vars);
	}
	if (vars->mlx)
	{
		free_vars_mlx(vars);
	}
	if (vars->line)
		free(vars->line);
}
