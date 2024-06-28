/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:58:43 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 12:59:16 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotation_up_transform(int *x, int *y, int dx, int dy)
{
	*x -= dx;
	*y -= dy;
}

void isometric_transform(int *x, int *y, int z, t_line *line)
{
    const double angle = M_PI / 6;
   	int temp_x = *x;
    int temp_y = *y;
	*x = (temp_x - temp_y) * cos(angle) + line->src_x;
	*y = (temp_x + temp_y) * sin(angle) - z + line->src_y;
}
