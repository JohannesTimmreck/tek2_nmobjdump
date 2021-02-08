/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#ifndef PSU_NMOBJDUMP_2019_NM_H
#define PSU_NMOBJDUMP_2019_NM_H

#include  <elf.h>
#include  <fcntl.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include  <sys/mman.h>
#include  <sys/stat.h>
#include <string.h>

typedef struct symbol_s
{
    Elf64_Addr value;
    unsigned char symbol;
    char *name;
    struct symbol_s *next;
    struct symbol_s *previous;
} symbol_t;

// check_args.c
int check_args(int ac, char **av);

// cmp.c
bool my_strcmp(char *str1, char *str2);

//get_elf.h
void *get_elf (int fd, char *filename);
int handle_file_name(char *file_name);

// get_symbol.c
symbol_t *get_nm_information(Elf64_Ehdr *elf);

// main.c
symbol_t *add_symbol(symbol_t *start, symbol_t *new);

// symbol_type.c
char assign_type(Elf64_Sym *sym_table_entry, Elf64_Shdr *sections);


#endif //PSU_NMOBJDUMP_2019_NM_H
