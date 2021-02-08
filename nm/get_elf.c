/*
** EPITECH PROJECT, 2019
** PSU_nmobjdump_2019
** File description:
** description
*/

#include "nm.h"

bool check_for_elf_format(void *buf)
{
    char *str = (char *)buf;

    if (str[0] == 127 && str[1] == 'E' && str[2] == 'L' && str[3] == 'F')
        return (true);
    else
        return (false);
}

void *get_elf (int fd, char *filename)
{
    struct stat s;
    void *buf = NULL;
    if (fstat(fd, &s) == -1) {
        fprintf(stderr, "nm: '%s': error in fstat\n", filename);
        return (NULL);
    }
    buf = mmap(NULL , s.st_size , PROT_READ , MAP_PRIVATE , fd, 0);
    if (buf != (void *)-1) {
        if (check_for_elf_format(buf)) {
            return (buf);
        } else {
            fprintf(stderr, "nm: %s", filename);
            fprintf(stderr, ": File format not recognized\n");
            return (NULL);
        }
    } else {
        fprintf(stderr, "nm: '%s': error in mmap\n", filename);
        return (NULL);
    }
}

int handle_file_name(char *file_name)
{
    int fd;
    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "nm: '%s': no such file\n", file_name);
        return -1;
    }
    return (fd);
}