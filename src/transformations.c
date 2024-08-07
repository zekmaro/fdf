/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:58:43 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 15:00:08 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_transform(int *x, int *y, int z, t_line *line)
{
	const double	angle = M_PI / 6;
	int				temp_x;
	int				temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = (temp_x - temp_y) * cos(angle) + line->src_x;
	*y = (temp_x + temp_y) * sin(angle) - z + line->src_y;
}

void	parallel_transform(int *x, int *y, int z, t_line *line)
{
	*x = *x + line->src_x;
	*y = *y - z + line->src_y;
}

void	rotation_x(int *y, int *z, double angle)
{
	int	temp_y;
	int	temp_z;

	temp_y = *y;
	temp_z = *z;
	*y = temp_y * cos(angle) - temp_z * sin(angle);
	*z = temp_y * sin(angle) + temp_z * cos(angle);
}

void	rotation_y(int *x, int *z, double angle)
{
	int	temp_x;
	int	temp_z;

	temp_x = *x;
	temp_z = *z;
	*x = temp_x * cos(angle) + temp_z * sin(angle);
	*z = -temp_x * sin(angle) + temp_z * cos(angle);
}

void	rotation_z(int *x, int *y, double angle)
{
	int	temp_x;
	int	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(angle) - temp_y * sin(angle);
	*y = temp_x * sin(angle) + temp_y * cos(angle);
}
