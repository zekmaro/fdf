/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:02:00 by anarama           #+#    #+#             */
/*   Updated: 2024/06/10 16:29:56 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <mlx.h>
# include <math.h>

// KEY DEFINITION
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define ESCAPE 65307

// COLORS
# define WHITE 0xFFFFFF
# define RED 0xFF0000

typedef struct s_map
{
	int 			**grid;
	unsigned long	**colors;
	int 			width;
	int 			length;
	int				max_height;
	int				min_height;
	int				step;
} t_map;

typedef struct s_color
{
	unsigned long color;
	int red;
	int green;
	int blue;
} t_color;

typedef struct s_colors
{
	t_color *white;
	t_color *red;
} t_colors;

typedef struct s_mlx
{
    void *mlx;
    void *win;
} t_mlx;

typedef struct s_vars 
{
	t_mlx *mlx;
	t_map *map;
} t_vars;

typedef struct s_line
{
    int x0, y0;
    int x1, y1;
} t_line;

//----UTILS----
void	free_memory(char **arr);
void	ft_free_map(t_map *map);
void	ft_print_map(t_map *map);
int		find_min(int num1, int num2);
void	ft_free_colors(t_map *map);
void	print_colors(t_map *map);
int		calculate_step(t_line *line, int window_width, int window_height, t_map *map);
//-------------

//---PARSING---
int count_new_lines(int fd);
int *convert_line_to_int_arr(char *str, t_map *map, int index);
int read_map(int fd, t_map *map, char *file_name);

//---DRAWING---
void	draw_plane(t_mlx *mlx, t_line *line, t_map *map, t_colors *colors);

//----COLORS-----
void	initialise_rgb(t_color *color);
int		get_red(unsigned long color);
int		get_green(unsigned long color);
int		get_blue(unsigned long color);

#endif // FDF_H
