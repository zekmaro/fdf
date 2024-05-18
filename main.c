/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/17 18:21:04 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int check_input(char *str)
{
	char **input;

	int
}

t_map *read_map(int fd)
{
	t_map *map;
	char *line;
	
	map = malloc(sizeof(t_map));
	if (!map)
	{
		perror("Error allocating map memory!");
		exit(EXIT_FAILURE);
	}
	map->length = 0;
	map->width = 0;
	while (1)
	{
		line = get_next_line(fd);
		
	}
}

int main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	
	if (argc > 2)
	{
		perror("More than 2 arguments!");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Invalid file descriptor!");
		exit(EXIT_FAILURE);
	}
	map = read_map(fd);
}