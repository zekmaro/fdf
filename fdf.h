/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:02:00 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 12:36:26 by anarama          ###   ########.fr       */
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
# define KEY_PLUS 65451 //scale up
# define KEY_MINUS 65453 //scale down
# define W 119
# define D 100
# define S 115
# define A 97
# define Q 113
# define E 101
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define ESCAPE 65307
# define SCALE_HEIGHTS_UP 65450
# define SCALE_HEIGHTS_DOWN 65455

// KEY DEFINITIONS MAC
// # define KEY_PLUS 30 //scale up
// # define KEY_MINUS 44 //scale down
// # define W 13
// # define D 2
// # define S 1
// # define A 0
// # define Q 12
// # define E 14
// # define KEY_LEFT 123
// # define KEY_RIGHT 124
// # define KEY_UP 126
// # define KEY_DOWN 125
// # define ESCAPE 53
// # define SCALE_HEIGHTS_UP 33
// # define SCALE_HEIGHTS_DOWN 35

// COLORS
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define PURPLE 0x800080
# define BLACK 0x000000

// for makefile compilation from linux: -lmlx -lXext -lX11 -lm -o
// for mac: -framework OpenGL -framework AppKit -o

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
	int				rotation_x;
	int				rotation_y;
	int				rotation_z;
} t_map;

typedef struct s_angles
{
	double angle_x;
	double angle_y;
	double angle_z;
} t_angles;

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
	unsigned long	color;
	int 			red;
	int 			green;
	int				blue;
} t_color;

typedef struct s_colors
{
	t_color	*white;
	t_color	*red;
} t_colors;

typedef struct s_mlx
{
    void	*mlx;
    void	*win;
	int		window_width;
	int		window_height;
} t_mlx;

typedef struct s_line
{
    int	x0;
	int	y0;
	int	z0;
    int	x1;
	int	y1;
	int	z1;
	int	src_x;
	int	src_y;
	int dx;
	int dy;
	int amount_pixels;
	int fraction;
	int	step_x;
	int step_y;
	int dh;
} t_line;

typedef struct s_vars 
{
	t_map		*map;
	t_img		*image;
	t_img		*color;
	t_colors	*colors;
	t_mlx		*mlx;
	t_line		*line;
} t_vars;

//----COLORS_HANDLING----
unsigned long	get_color(char *str);
//-----------------------

//----DRAW_LINE----
void draw_line(t_vars *vars, unsigned long color,  int height);
//-----------------

//----DRAW_MAP----
void	draw_map(t_vars *vars);
//----------------

//---GRADIENT---
int				get_red(unsigned long color);
int				get_green(unsigned long color);
int 			get_blue(unsigned long color);
void			initialise_rgb(t_color *color);
int				interpolate(int start_component, int end_component, t_map *map, int height);
unsigned long	combine_rgb(int red, int green, int blue);
unsigned long	calculate_gradient(t_color *color_start, t_color *color_end, t_map *map, int height);
//-------------

//----IMAGE_HANDLING----
void	clean_screen(t_vars *vars);
void	get_data_image(t_img *image, t_mlx *mlx);
void	put_pixel_to_image(t_img *image, int x, int y, int color);
//----------------------
//---INITIALISATION---
void	initialise_vars(t_vars *vars);
void	initialise_map_vars(t_vars *vars);
void	inititalise_angles(t_angles *angles, t_vars *vars);
//--------------------

//----KEY_HANDLING----
int	key_hook(int keycode, t_vars *vars);
//--------------------

//----MEMEMORY_FREEING---
void	free_memory(char **arr);
void 	free_map(t_map *map);
void 	free_map_colors(t_map *map);
void	cleanup_vars(t_vars *vars);
void	free_and_exit(t_vars *vars);
//-------------

//----PARSING--
int	read_map(int fd, t_map *map, char *file_name);
//-------------

//----PRINTING--
void	ft_print_map(t_map *map);
void 	print_colors(t_map *map);
//-------------

//----ROTATIONS--
void	rotate_up(t_map *map);
void	rotate_down(t_map *map);
//-------------

//----TRANSFORMATION--
void	isometric_transform(int *x, int *y, int z, t_line *line);
void	rotation_x(int *y, int *z, double angle);
void	rotation_y(int *x, int *z, double angle);
void	rotation_z(int *x, int *y, double angle);
//-------------

//----UNTILS--
int		ft_min(const int num1, const int num2);
int		ft_max(const int num1, const int num2);
int		calculate_step(t_vars *vars);
void	calculate_center(t_map *map);
void	get_max_height(t_map *map);
void	get_min_height(t_map *map);
//-------------
#endif // FDF_H
