/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "objdump.h"

int objdump(char *filename)
{
    int fd = handle_file_name(filename);
    Elf64_Ehdr *elf = NULL;
    if (fd == -1)
        return (1);
    elf = get_elf(fd, filename);
    if (elf == NULL) {
        close(fd);
        return (1);
    }
    if (elf->e_ident[EI_CLASS] == ELFCLASS64) {
        printf("\n%s:     file format elf64-x86-64\n", filename);
        objdump_64(elf);
    } else if (elf->e_ident[EI_CLASS] == ELFCLASS32) {
        printf("\n%s:     file format elf32-i386\n", filename);
        objdump_32((Elf32_Ehdr *)elf);
    }
    close(fd);
    return (0);
}

int check_argument(int ac, char **av)
{
    int error = 0;
    int args = 0;

    for (int i = 1; i < ac; ++i) {
        if (av[i][0] == '-' && (av[i][1] == 'f' || av[i][1] == 's'))
            continue;
        args += 1;
    }
    if (args == 0)
        return (objdump("a.out"));
    for (int i = 1; i < ac; ++i) {
        if (av[i][0] == '-' && (av[i][1] == 'f' || av[i][1] == 's'))
            continue;
        error += objdump(av[i]);
    }
    return (error);
}

int main(int ac , char **av)
{
    if (check_argument(ac, av) != 0)
        return (84);
    return (0);
}
