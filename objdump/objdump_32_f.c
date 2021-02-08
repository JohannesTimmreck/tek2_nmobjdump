/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "objdump.h"

static unsigned int get_flags(Elf32_Ehdr *ehdr, Elf32_Shdr *sections)
{
    unsigned int flags = BFD_NO_FLAGS;

    if (ehdr->e_type == ET_EXEC)
        flags += EXEC_P + D_PAGED;
    else if (ehdr->e_type == ET_DYN)
        flags += DYNAMIC + D_PAGED;
    if (ehdr->e_type == ET_REL)
        flags += HAS_RELOC;
    for (int i = 0; i < ehdr->e_shnum; ++i) {
        if (sections[i].sh_type == SHT_SYMTAB)
            flags += HAS_SYMS;
    }
    return (flags);
}

void apply_32_f_flag(Elf32_Ehdr *ehdr)
{
    printf("architecture: i386:x86-32, flags ");
    print_flags1(get_flags(ehdr,
        (Elf32_Shdr *)((char *)ehdr + ehdr->e_shoff)));
    printf("\n");
    if (ehdr->e_entry != 0)
        printf("start address %018p\n", ehdr->e_entry);
    else
        printf("start address 0x0000000000000000\n");
}