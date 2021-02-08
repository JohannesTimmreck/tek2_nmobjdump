/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

int check_args(int ac, char **av)
{
    for (int i = 0; i < ac; ++i) {
        if (av[i][0] == '-') {
            fprintf(stderr, "nm: flag %s not supported\n", av[i]);
            return (1);
        }
    }
    return (0);
}
