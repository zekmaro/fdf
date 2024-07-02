/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:26:36 by anarama           #+#    #+#             */
/*   Updated: 2024/07/02 15:58:56 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_new_lines(int fd)
{
	char	buffer;
	int		read_bytes;
	int		new_lines;

	read_bytes = 1;
	new_lines = 0;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, &buffer, 1);
		if (read_bytes < 0)
		{
			perror("read");
			return (-1);
		}
		if (buffer == '\n')
			new_lines++;
	}
	return (new_lines);
}

void	convert(char **temp, int *row, t_map *map, int index)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (row && temp[i] != NULL && temp[i][0] != '\n')
	{
		row[i] = ft_atoi(temp[i]);
		map->colors[index][i] = get_color(temp[i]);
		if (flag == 0 && map->colors[index][i] != WHITE)
		{
			map->colorized = 1;
			flag = 1;
		}
		i++;
	}
}

int	*convert_line_to_int_arr(char *str, t_map *map, int index)
{
	char	**temp;
	int		i;
	int		*row;

	temp = ft_split(str, ' ');
	if (!temp)
		return (NULL);
	i = 0;
	map->length = 0;
	while (temp[i] != NULL && temp[i][0] != '\n')
	{
		(map->length)++;
		i++;
	}
	row = ft_calloc(map->length, sizeof(int));
	map->colors[index] = ft_calloc(map->length, sizeof(unsigned long));
	if (!row || !map->colors[index])
	{
		free_memory(temp);
		free(row);
		return (NULL);
	}
	convert(temp, row, map, index);
	free_memory(temp);
	return (row);
}

int	fill_the_map(int fd, t_map *map)
{
	int		i;
	int		save_length;
	char	*line;

	i = 0;
	while (i < map->width)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), get_next_line(-1), 0);
		map->grid[i] = convert_line_to_int_arr(line, map, i);
		free(line);
		if (map->grid[i] == NULL)
			return (close(fd), get_next_line(-1), 0);
		if (i == 0)
			save_length = map->length;
		else if (i != 0 && (save_length != map->length))
			return (close(fd), get_next_line(-1), 0);
		i++;
	}
	return (1);
}

int	read_map(int fd, t_map *map, char *file_name)
{
	map->width = count_new_lines(fd);
	map->width--;
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || map->width <= 0)
		return (0);
	map->grid = (int **)ft_calloc(map->width, sizeof(int *));
	map->colors = (unsigned long **)ft_calloc(map->width, sizeof(int *));
	if (!map->grid || !map->colors)
	{
		close(fd);
		return (0);
	}
	if (!fill_the_map(fd, map))
		return (0);
	return (close(fd), get_next_line(-1), 1);
}
