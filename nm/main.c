/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

symbol_t *sort(symbol_t *start, symbol_t *prev, symbol_t *new, bool cmp)
{
    if (prev->previous == NULL && cmp == false) {
        new->next = prev;
        prev->previous = new;
        return (new);
    } else if (prev->next == NULL && cmp == true) {
        prev->next = new;
        new->previous = prev;
    } else {
        prev->previous->next = new;
        new->previous = prev->previous;
        prev->previous = new;
        new->next = prev;
    }
    return (start);
}

symbol_t *add_symbol(symbol_t *start, symbol_t *new)
{
    symbol_t *tmp = start;
    bool cmp;
    if (new == NULL)
        return (start);
    if (start == NULL) {
        start = new;
        return (start);
    }
    for (; (cmp = my_strcmp(tmp->name, new->name))
            && tmp->next != NULL; tmp = tmp->next);
    return (sort(start, tmp, new, cmp));
}

int print_nm_information(symbol_t *symbols)
{
    if (symbols == NULL)
        return (1);
    for (symbol_t *tmp = symbols; tmp != NULL ; tmp = tmp->next) {
        if (tmp->symbol != 'U' && tmp->symbol != 'w')
            printf("%016lx %c %s\n", tmp->value, tmp->symbol, tmp->name);
        else
            printf("                 %c %s\n", tmp->symbol, tmp->name);
    }
    for (symbol_t *tmp = symbols; tmp != NULL; tmp = symbols) {
        symbols = symbols->next;
        free(tmp);
    }
    return (0);
}

int nm(char * filename, bool multiple)
{
    int fd = handle_file_name(filename);
    symbol_t *symbols = NULL;
    Elf64_Ehdr *elf = NULL;
    if (fd == -1)
        return (1);
    elf = get_elf(fd, filename);
    if (elf == NULL) {
        close(fd);
        return (1);
    }
    if (multiple)
        printf("\n%s:\n", filename);
    symbols = get_nm_information(elf);
    if (print_nm_information(symbols) != 0) {
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

int main(int ac, char **av)
{
    bool multiple = false;
    int error = 0;

    if (check_args(ac, av) != 0)
        return (84);
    if (ac > 2)
        multiple = true;
    else if (ac == 1)
        error += nm("a.out", false);
    for (int i = 1; i < ac; ++i)
        error += nm(av[i], multiple);
    if (error != 0)
        return (84);
    return (0);
}