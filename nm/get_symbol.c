/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

void get_sections (Elf64_Ehdr *elf, Elf64_Shdr **sym_table,
                    Elf64_Shdr **str_table, Elf64_Shdr *sections)
{
    char *str = (char *) ((char *)elf + sections[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i++) {
        if (!sections[i].sh_size)
            continue;
        if (strcmp(&str[sections[i].sh_name], ".strtab") == 0) {
            *str_table = &sections[i];
        } else if (sections[i].sh_type == SHT_SYMTAB) {
            *sym_table = &sections[i];
        }
    }
}

bool filter_name(char *name)
{
    size_t len = strlen(name);
    if (strcmp(name, "") == 0 || name[0] == '.')
        return (false);
    else if (name[len - 1] == 'c' && name[len - 2] == '.')
        return (false);
    return (true);
}

symbol_t *assign_symbol_information(Elf64_Sym *sym_table_entry,
    Elf64_Shdr *sections, char * str)
{
    symbol_t *symbol = malloc(sizeof(symbol_t));

    if (symbol == NULL)
        return (NULL);
    symbol->value = sym_table_entry->st_value;
    symbol->name = str + sym_table_entry->st_name;
    symbol->symbol = assign_type(sym_table_entry, sections);
    symbol->next = NULL;
    symbol->previous = NULL;
    return symbol;
}

symbol_t *get_nm_information(Elf64_Ehdr *elf)
{
    Elf64_Shdr *sym_t = NULL;
    Elf64_Shdr *str_table = NULL;
    Elf64_Sym *sym_entries = NULL;
    symbol_t *symbols = NULL;
    Elf64_Shdr *sections = (Elf64_Shdr *)((char *)elf + elf->e_shoff);
    char *str;

    get_sections(elf, &sym_t, &str_table, sections);
    if (sym_t == NULL || str_table == NULL)
        return NULL;
    sym_entries = (Elf64_Sym *)((void *)elf + sym_t->sh_offset);
    str = (char *) ((void *)elf + str_table->sh_offset);
    for (long unsigned int i = 0; i < sym_t->sh_size / sym_t->sh_entsize; ++i) {
        if (!filter_name(str + sym_entries[i].st_name))
            continue;
        symbols = add_symbol(symbols,
            assign_symbol_information(&sym_entries[i], sections, str));
    }
    return (symbols);
}
