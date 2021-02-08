/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "objdump.h"

static void print_linestart(uint64_t line_start, uint64_t max_size, char *str)
{
    int loops = 0;

    for (; line_start < max_size;) {
        loops += 1;
        printf("%02x", (unsigned char)str[line_start]);
        ++line_start;
        if (line_start % 16 == 0) {
            printf(" ");
            break;
        } else if (line_start % 4 == 0)
            printf(" ");
    }
    for (; loops < 16;) {
        ++loops;
        if (loops % 4 == 0)
            printf(" ");
        printf("  ");
    }
    printf(" ");
}

static void print_last_spaces(uint64_t i)
{
    for (; i % 16 != 0;) {
        ++i;
        printf(" ");
        if (i % 16 == 0)
            printf("\n");
    }
}

static void print_section(Elf64_Shdr *section, void *buffer)
{
    char *str = buffer + section->sh_offset;
    unsigned int line_start = section->sh_addr;
    uint64_t i = 0;

    for (; i < section->sh_size; i++) {
        if (i % 16 == 0) {
            printf(" %04x ", line_start);
            print_linestart(i, section->sh_size, str);
            line_start += 16;
        }
        if (str[i] >= ' ' && str[i] <= '~')
            printf("%c", str[i]);
        else
            printf(".");
        if (i % 16 == 15)
            printf("\n");
    }
    print_last_spaces(i);
}

void apply_s_flag(Elf64_Ehdr *ehdr)
{
    Elf64_Shdr *sections = (Elf64_Shdr *)((char *)ehdr + ehdr->e_shoff);
    char *str = (char *) ((char *)ehdr + sections[ehdr->e_shstrndx].sh_offset);

    for (int i = 1; i < ehdr->e_shnum; ++i) {
        if ((str + sections[i].sh_name)[0] == '\0'
            || strcmp(str + sections[i].sh_name, ".bss") == 0
            || strcmp(str + sections[i].sh_name, ".shstrtab") == 0
            || strcmp(str + sections[i].sh_name, ".symtab") == 0
            || strcmp(str + sections[i].sh_name, ".strtab") == 0)
            continue;
        printf("Contents of section %s:\n", str + sections[i].sh_name);
        print_section(&sections[i], ehdr);
    }
}

void objdump_64(Elf64_Ehdr *ehdr)
{
    apply_f_flag(ehdr);
    printf("\n");
    apply_s_flag(ehdr);
}