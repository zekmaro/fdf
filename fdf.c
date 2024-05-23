/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/23 21:51:38 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int check_input(char *str)
// {
// 	char	**input;

// 	int		
// }
void	ft_free_memory(t_map *map)
{
	int i;

	i = 0;
	while (i < map->width)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	ft_print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->length)
		{
			ft_printf("%d ", *map->grid[0]);
			j++;
		}
		ft_printf("\n");
	}
}

int count_new_lines(int fd)
{
	char buffer;
	int read_bytes;
	int new_lines;

	read_bytes = 1;
	new_lines = 0;
	while (read_bytes == 1)
	{
		read_bytes = read(fd, &buffer, 1); // protection is missing
		if (buffer == '\n')
			new_lines++;
	}
	return (new_lines);
}

int	*convert_line_to_int_arr(char *str, int *length)
{
	char **temp;
	int i;
	int *row;

	temp = ft_split(str, ' ');
	if (!temp)
	{
		exit(1);
	}
	i = 0;
	*length = 0;
	while (temp[i] != NULL)
	{
		(*length)++;
		i++;
	}
	row = malloc(sizeof(int) * (*length));
	if (!row)
		exit(1); // WORK ON FREEING EVERYTING
	i = 0;
	while (temp[i] != NULL)
	{
		row[i] = ft_atoi(temp[i]);
		i++;
	}
	return (row);
}

void read_map(int fd, t_map *map)
{
	char *line;
	int i;
	int save_length;

	if (!map)
	{
		perror("Error allocating map memory!");
		exit(EXIT_FAILURE);
	}
	map->width = count_new_lines(fd); // edge case if returned 0
	map->grid = (int **)malloc(sizeof(int *) * map->width);
	save_length = 0;
	i = 0;
	while (i < map->width)
	{
		line = get_next_line(fd); // open & close again loshara
		map->grid[i] = convert_line_to_int_arr(line, &(map->length));
		if (i == 0)
			save_length = map->length;
		else if (i != 0 && (save_length != map->length))
			exit(1); //somehow stop and free cause length is not the same anymore
		i++;
	}
}

int main(int argc, char **argv)
{
	// int		fd;
	// t_map	map;
	(void) argv;	
	if (argc > 2)
	{
		perror("More than 2 arguments!\n");
		exit(EXIT_FAILURE);
	}
	// fd = open(argv[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror("Invalid file descriptor!\n");
	// 	exit(EXIT_FAILURE);
	// }
	// ft_bzero(&map, sizeof(t_map));
	// read_map(fd, &map);
	// ft_print_map(&map);
	// ft_free_memory(&map);
	// close(fd);
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	return (0);
}