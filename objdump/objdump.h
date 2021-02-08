/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#ifndef PSU_NMOBJDUMP_2019_OBJDUMP_H
#define PSU_NMOBJDUMP_2019_OBJDUMP_H

#include  <fcntl.h>
#include  <stdio.h>
#include  <elf.h>
#include  <sys/mman.h>
#include  <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "libelf.h"

#include "flags.h"

// get_elf.c
void *get_elf (int fd, char *filename);
int handle_file_name(char *file_name);

// objdump_32.c
void objdump_32(Elf32_Ehdr *ehdr);

// objdump_64.c
void objdump_64(Elf64_Ehdr *ehdr);

// objdump_32_f.c
void apply_32_f_flag(Elf32_Ehdr *ehdr);

// objdump_64_f.c
void apply_f_flag(Elf64_Ehdr *ehdr);

// print_flags.c
void print_flags1(unsigned int flags);

#endif //PSU_NMOBJDUMP_2019_OBJDUMP_H
