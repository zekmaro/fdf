/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:26:36 by anarama           #+#    #+#             */
/*   Updated: 2024/06/01 19:20:50 by anarama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned long hex_to_color(const char *hex)
{
    unsigned long color = 0;
    int i = 0;

    // Skip the "0x" or "0X" prefix if present
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
    {
        hex += 2;
    }

    // Convert hex string to unsigned long
    while (hex[i] != '\0')
    {
        color <<= 4;  // Shift left by 4 bits to make room for the next digit
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            color |= (hex[i] - '0');
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            color |= (hex[i] - 'a' + 10);
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            color |= (hex[i] - 'A' + 10);
        }
        else
        {
            // Invalid character found, return default color
            return hex_to_color("FFFFFF");
        }
        i++;
    }

    return color;
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

int check_valid_hex(char *str)
{
    int i = 0;

    // Check for "0x" or "0X" prefix
    if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
        return 0;

    i = 2;
    while (str[i])
    {
        if (!ft_strchr("0123456789ABCDEFabcdef", str[i]))
            return 0;
        i++;
    }
    return 1;
}


unsigned long get_color(char *str)
{
    char **temp;
    unsigned long color;

    temp = ft_split(str, ',');
    color = hex_to_color("FFFFFF"); // Default color (white)
    if (temp[1] && check_valid_hex(temp[1]))
    {
        color = hex_to_color(temp[1]);
    }
    free_memory(temp);
    return (color);
}


int *convert_line_to_int_arr(char *str, t_map *map, int index)
{
    char **temp;
    int i;
    int *row;

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
    i = 0;
    while (row && temp[i] != NULL && temp[i][0] != '\n')
    {
        row[i] = ft_atoi(temp[i]);
		map->colors[index][i] = get_color(temp[i]);
        i++;
    }
    free_memory(temp);
    return (row);
}

int read_map(int fd, t_map *map, char *file_name)
{
    char *line;
    int i;
    int save_length;

    map->width = count_new_lines(fd); // Handle edge case if returned 0
	map->width--; // hardcode cause i dont want to count the last new line
	close(fd);
	fd = open(file_name, O_RDONLY);
    if (fd < 0 || map->width <= 0)
		return (0);
    map->grid = (int **)ft_calloc(map->width, sizeof(int *));
	map->colors = (unsigned long **)ft_calloc(map->width, sizeof(int *));
    if (!map->grid || !map->colors)
    	return (close(fd), 0);
    save_length = 0;
    i = 0;
    while (i < map->width)
    {
        line = get_next_line(fd);
        if (!line)
            return (close(fd), 0);
        map->grid[i] = convert_line_to_int_arr(line, map, i);
        free(line);
        if (map->grid[i] == NULL)
            return (close(fd), 0);
        if (i == 0)
            save_length = map->length;
        else if (i != 0 && (save_length != map->length))
            return (close(fd), 0);
        i++;
    }
	return (close(fd), 1);
}