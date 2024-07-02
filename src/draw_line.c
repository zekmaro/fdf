/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:14:52 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 17:03:01 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	define_step(const int a, const int b)
{
	if (a < b)
		return (1);
	else if (a > b)
		return (-1);
	else
		return (0);
}

void	calculate_fraction(t_line *line)
{
	if (line->dh)
	{
		line->fraction = line->amount_pixels / abs(line->dh);
	}
	while (line->dh && line->fraction * abs(line->dh)
		< line->amount_pixels + line->amount_pixels / 2)
	{
		line->fraction++;
	}
}

void	get_line_data(t_line *line)
{
	line->step_x = define_step(line->x0, line->x1);
	line->step_y = define_step(line->y0, line->y1);
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	line->amount_pixels = sqrt(line->dx * line->dx + line->dy * line->dy);
	calculate_fraction(line);
}

void	increment_step(int *x0, int *y0, t_line *line)
{
	int	error;

	error = abs(*x0 - line->x0) * line->dy - abs(*y0 - line->y0) * line->dx;
	if (line->step_x && !error)
	{
		*x0 += line->step_x;
	}
	else if (line->step_y && !error)
	{
		*y0 += line->step_y;
	}
	else if (error < 0)
	{
		*x0 += line->step_x;
	}
	else if (error > 0)
	{
		*y0 += line->step_y;
	}
}

void	draw_line(t_vars *vars, unsigned long color, int height)
{
	int	x0;
	int	y0;
	int	i;

	get_line_data(vars->line);
	i = 0;
	x0 = vars->line->x0;
	y0 = vars->line->y0;
	while (1)
	{
		color = calculate_gradient(vars->colors->low,
				vars->colors->top, vars->map, height);
		put_pixel_to_image(vars, x0, y0, color);
		if (vars->line->fraction && i % vars->line->fraction == 0)
		{
			if (vars->line->dh > 0)
				height++;
			else if (vars->line->dh < 0)
				height--;
		}
		if (x0 == vars->line->x1 && y0 == vars->line->y1)
			break ;
		increment_step(&x0, &y0, vars->line);
		i++;
	}
}
