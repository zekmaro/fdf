/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:02:00 by anarama           #+#    #+#             */
/*   Updated: 2024/05/27 17:31:34 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <mlx.h>
# include <math.h>


typedef struct s_map
{
	int **grid;
	int width;
	int length;
	int *color;
} t_map;

typedef struct s_line
{
    int x0, y0;
    int x1, y1;
} t_line;

typedef struct s_mlx
{
    void *mlx;
    void *win;
} t_mlx;

//----UTILS----
void	free_memory(char **arr);
void	ft_free_map(t_map *map);
void	ft_print_map(t_map *map);
//-------------

//---PARSING---
int count_new_lines(int fd);
int *convert_line_to_int_arr(char *str, int *length);
int read_map(int fd, t_map *map, char *file_name);

#endif