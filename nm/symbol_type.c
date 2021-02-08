/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

void check_shdr(Elf64_Shdr *section, char *c)
{
    if (section->sh_type == SHT_NOBITS &&
        section->sh_flags == (SHF_ALLOC | SHF_WRITE))
        *c = 'B';
    if (section->sh_type == SHT_DYNAMIC || (section->sh_type == SHT_PROGBITS &&
        section->sh_flags == (SHF_ALLOC | SHF_WRITE)))
        *c = 'D';
    if (section->sh_type == SHT_PROGBITS && (section->sh_flags == SHF_ALLOC ||
                                section->sh_flags == (SHF_MERGE | SHF_ALLOC)))
        *c = 'R';
    if ((section->sh_type == SHT_PROGBITS
        && section->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        || section->sh_type == SHT_INIT_ARRAY
        || section->sh_type == SHT_FINI_ARRAY)
        *c = 'T';
}

void check_macro(unsigned char info, char *c)
{
    if (ELF64_ST_BIND(info) == STB_WEAK) {
        if (ELF64_ST_TYPE(info) == STT_OBJECT)
            *c = 'V';
        else
            *c = 'W';
    }
}

void check_shndx(Elf64_Section shndx, char *c)
{
    if (shndx == SHN_ABS)
        *c = 'A';
    if (shndx == SHN_COMMON)
        *c = 'C';
    if (shndx == SHN_UNDEF)
        *c = 'U';
}

char assign_type(Elf64_Sym *sym_table_entry, Elf64_Shdr *sections)
{
    char  c = 0;

    if (ELF64_ST_BIND(sym_table_entry->st_info) == STB_GNU_UNIQUE)
        return ('u');
    check_macro(sym_table_entry->st_info, &c);
    if (c == 0)
        check_shdr(&sections[sym_table_entry->st_shndx], &c);
    if (c == 0)
        check_shndx(sym_table_entry->st_shndx, &c);
    if ((ELF64_ST_BIND(sym_table_entry->st_info) == STB_LOCAL && c != 0)
        || ((c == 'W' || c == 'V') && sym_table_entry->st_shndx == SHN_UNDEF))
        c += 32;
    return c;
}