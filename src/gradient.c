/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:35:14 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 10:41:45 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int get_red(unsigned long color)
{
    return ((color >> 16) & 0xFF);
}

int get_green(unsigned long color)
{
    return ((color >> 8) & 0xFF);
}

int get_blue(unsigned long color)
{
    return (color & 0xFF);
}

void	initialise_rgb(t_color *color)
{
	color->red = get_red(color->color);
	color->green = get_green(color->color);
	color->blue = get_blue(color->color);
}

int	interpolate(int start_component, int end_component, t_map *map, int height)
{
	int result;
	const int dh = map->max_height - map->min_height;
	const int d_rgb = end_component - start_component;
	if (dh == 0)
		return (start_component);
	result = start_component + d_rgb * (height - map->min_height) / dh;
	return (result);
}

unsigned long	combine_rgb(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

unsigned long	calculate_gradient(t_color *color_start, t_color *color_end, t_map *map, int height)
{
	unsigned long result;
	int result_red;
	int result_green;
	int result_blue;

	result_red = interpolate(color_start->red, color_end->red, map, height);
	result_green = interpolate(color_start->green, color_end->green, map, height);
	result_blue = interpolate(color_start->blue, color_end->blue, map, height);
	result = combine_rgb(result_red, result_green, result_blue);
	return (result);
}
