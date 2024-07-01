/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:43:01 by anarama           #+#    #+#             */
/*   Updated: 2024/07/01 16:02:16 by anarama          ###   ########.fr       */
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

    return (color);
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