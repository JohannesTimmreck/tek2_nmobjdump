/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "objdump.h"

unsigned int print_commma(unsigned int flags, unsigned int tmp,
    unsigned int flag)
{
    flags -= flag;
    if (flags != 0 && flags != tmp)
        printf(", ");
    return (flags);
}

void print_flags2(unsigned int flags, unsigned int tmp)
{
    if ((flags & HAS_SYMS) != 0 && flags != 0) {
        printf("HAS_SYMS");
        flags = print_commma(flags, tmp, HAS_SYMS);
    }
    if ((flags & HAS_LOCALS) != 0 && flags != 0) {
        printf("EXEC_P");
        flags = print_commma(flags, tmp, HAS_LOCALS);
    }
    if ((flags & DYNAMIC) != 0 && flags != 0) {
        printf("DYNAMIC");
        flags = print_commma(flags, tmp, DYNAMIC);
    }
    if ((flags & D_PAGED) != 0 && flags != 0) {
        printf("D_PAGED");
        flags = print_commma(flags, tmp, D_PAGED);
    }
}

void print_flags1(unsigned int flags)
{
    unsigned int tmp = flags;
    printf("%010p:\n", flags);
    if ((flags & BFD_NO_FLAGS) != 0)
        printf("BFD_NO_FLAG");
    if ((flags & HAS_RELOC) != 0 && flags != 0) {
        printf("HAS_RELOC");
        flags = print_commma(flags, tmp, HAS_RELOC);
    }
    if ((flags & EXEC_P) != 0 && flags != 0) {
        printf("EXEC_P");
        flags = print_commma(flags, tmp, EXEC_P);
    }
    if ((flags & HAS_DEBUG) != 0 && flags != 0) {
        printf("HAS_DEBUG");
        flags = print_commma(flags, tmp, HAS_DEBUG);
    }
    print_flags2(flags, tmp);
}