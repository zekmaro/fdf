/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrejarama <andrejarama@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:02:00 by anarama           #+#    #+#             */
/*   Updated: 2024/06/28 12:33:59 by andrejarama      ###   ########.fr       */
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
# include "minilibx_macos/mlx.h"
# include <math.h>

// KEY DEFINITION LINUX
// # define KEY_PLUS 65451 //scale up
// # define KEY_MINUS 65453 //scale down
// # define W 119
// # define D 100
// # define S 115
// # define A 97
// # define KEY_LEFT 65361
// # define KEY_RIGHT 65363
// # define KEY_UP 65362
// # define KEY_DOWN 65364
// # define ESCAPE 65307

// KEY DEFINITIONS MAC
# define KEY_PLUS 30 //scale up
# define KEY_MINUS 44 //scale down
# define W 13
# define D 2
# define S 1
# define A 0
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define ESCAPE 53

// COLORS
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PURPLE 0x800080
# define BLACK 0x000000

typedef struct s_map
{
	int 			**grid;
	unsigned long	**colors;
	int 			width;
	int 			length;
	int				max_height;
	int				min_height;
	int				step;
	int				center_x;
	int				center_y;
} t_map;

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bits_per_pixel;
    int		line_len;
    int		endian;
}	t_img;

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
	int window_width;
	int	window_height;
} t_mlx;

typedef struct s_line
{
    int x0, y0;
    int x1, y1;
	int src_x;
	int src_y;
} t_line;

typedef struct s_vars 
{
	t_map *map;
	t_img *image;
	t_img *color;
	t_colors *colors;
	t_mlx *mlx;
	t_line *line;
} t_vars;

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

//----UTILS----
void	free_memory(char **arr);
void	ft_free_map(t_map *map);
void	ft_print_map(t_map *map);
int		find_min(int num1, int num2);
void	ft_free_colors(t_map *map);
void	print_colors(t_map *map);
int		calculate_step(t_vars *vars);
//-------------

//---PARSING---
int count_new_lines(int fd);
int *convert_line_to_int_arr(char *str, t_map *map, int index);
int read_map(int fd, t_map *map, char *file_name);

//---DRAWING---
void	draw_plane(t_img *image, t_line *line, t_map *map, t_colors *colors);
void	put_pixel_to_image(t_img *image, int x, int y, int color);

//----COLORS-----
void	initialise_rgb(t_color *color);
int		get_red(unsigned long color);
int		get_green(unsigned long color);
int		get_blue(unsigned long color);

//----INITIALS-----
void	initialise_colors(t_colors *colors);
void	initialise_mlx(t_mlx *mlx);
void	initialise_line(t_line *line);
void	initialise_image(t_img *image, t_mlx *mlx);

#endif // FDF_H
