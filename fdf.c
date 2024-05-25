/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:36:25 by anarama           #+#    #+#             */
/*   Updated: 2024/05/25 16:12:38 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_memory(char **arr)
{
	char	**temp;

	temp = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(temp);
}

void ft_free_map(t_map *map)
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

void ft_print_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->width)
    {
        j = 0;
        while (j < map->length)
        {
            ft_printf("%d ", map->grid[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

int count_new_lines(int fd)
{
    char buffer;
    int read_bytes;
    int new_lines;

    read_bytes = 1;
    new_lines = 0;
    while (read_bytes > 0)
    {
		read_bytes = read(fd, &buffer, 1);
        if (buffer == '\n')
            new_lines++;
    }
    if (read_bytes == -1) // Error handling for read
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    return (new_lines);
}

int *convert_line_to_int_arr(char *str, int *length)
{
    char **temp;
    int i;
    int *row;

    temp = ft_split(str, ' ');
    if (!temp)
    {
        return NULL;
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
    {
        free_memory(temp); // Ensure to free split array
        return NULL;
    }
    i = 0;
    while (temp[i] != NULL)
    {
        row[i] = ft_atoi(temp[i]);
        i++;
    }
    free_memory(temp); // Free the split array to avoid memory leak
    return (row);
}

void read_map(int fd, t_map *map, char *file_name)
{
    char *line;
    int i;
    int save_length;

    map->width = count_new_lines(fd); // Handle edge case if returned 0
	close(fd);
    if (map->width == 0)
    {
        perror("Empty or invalid file!\n");
        exit(EXIT_FAILURE);
    }
    map->grid = (int **)malloc(sizeof(int *) * map->width);
    if (!map->grid)
    {
        perror("Memory allocation error for grid!\n");
        exit(EXIT_FAILURE);
    }
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
		ft_free_map(map);
        perror("Invalid file descriptor!\n");
        exit(EXIT_FAILURE);
    }
    save_length = 0;
    i = 0;
    while (i < map->width)
    {
        line = get_next_line(fd); // Handle potential NULL return
        if (!line)
        {
            ft_free_map(map);
            perror("Error reading line!\n");
            close(fd);
            exit(EXIT_FAILURE);
        }
        map->grid[i] = convert_line_to_int_arr(line, &(map->length));
        free(line);
        if (map->grid[i] == NULL)
        {
            ft_free_map(map);
            close(fd);
            perror("Error allocating map memory!\n");
            exit(EXIT_FAILURE);
        }
        if (i == 0)
            save_length = map->length;
        else if (i != 0 && (save_length != map->length))
        {
            ft_free_map(map);
            close(fd);
            perror("Inconsistent row length!\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    close(fd);
}

int main(int argc, char **argv)
{
    int fd;
    t_map map;

    if (argc != 2)
    {
        perror("Usage: ./fdf <filename>\n");
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Invalid file descriptor!\n");
        exit(EXIT_FAILURE);
    }
    ft_bzero(&map, sizeof(t_map));
    read_map(fd, &map, argv[1]);
    ft_print_map(&map);
    ft_free_map(&map);
    return (0);
}

// Leaking one byte probably because of GNL somewhere