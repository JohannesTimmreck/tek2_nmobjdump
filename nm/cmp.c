/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

int my_charcasecmp(char c1, char c2)
{
    if (c1 >= 'a' && c1 <= 'z')
        c1 -= 32;
    if (c2 >= 'a' && c2 <= 'z')
        c2 -= 32;
    if (c1 < c2)
        return (-1);
    else if (c1 > c2)
        return (1);
    else
        return (0);
}

unsigned int get_first_char(char *str)
{
    unsigned int pos = 0;

    for (; str[pos] == '_'; ++pos);
    return (pos);
}

bool my_strcmp(char *str1, char *str2)
{
    unsigned int pos1 = get_first_char(str1);
    unsigned int pos2 = get_first_char(str2);
    int cmp = 0;

    while (str1[pos1] != '\0' && str2[pos2] != '\0') {
        for (;str1[pos1] == '_'; pos1++);
        for (;str2[pos2] == '_'; pos2++);
        cmp = my_charcasecmp(str1[pos1++], str2[pos2++]);
        if (cmp == -1)
            return (true);
        if (cmp == 1)
            return (false);
    }
    if (str1[pos1] == '\0' && str2[pos2] != '\0')
        return (true);
    else if (str1[pos1] != '\0' && str2[pos2] == '\0')
        return (false);
    if (pos1 >= pos2)
        return (true);
    return (false);
}
