/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:02:00 by anarama           #+#    #+#             */
/*   Updated: 2024/05/17 18:37:47 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>


typedef struct 
{
	int **grid;
	int width;
	int length;
} t_map;

#endif