##
## EPITECH PROJECT, 2019
## PSU_nmobjdump_2019
## File description:
## Makefile
##

SRC_NM	=		nm/main.c	\
				nm/check_args.c	\
				nm/cmp.c	\
				nm/get_elf.c	\
				nm/get_symbol.c	\
				nm/symbol_type.c	\

SRC_DMP	=		objdump/main.c	\
				objdump/get_elf.c	\
				objdump/print_flags.c	\
				objdump/objdump_32.c	\
				objdump/objdump_32_f.c	\
				objdump/objdump_64.c	\
				objdump/objdump_64_f.c	\

OBJ_NM	=		$(SRC_NM:.c=.o)

OBJ_DMP	=		$(SRC_DMP:.c=.o)

NAME_NM	=		my_nm

NAME_DMP	=	my_objdump

CC			=	gcc

CFLAGS +=		-g -W -Wall -Wextra

RM	=			@rm -rf

all:			nm objdump

nm:			$(OBJ_NM)
				@echo "Generation of binary $(NAME_NM)..."
				$(CC) -o $(NAME_NM) $(OBJ_NM)

objdump:		$(OBJ_DMP)
				@echo "Generation of binary $(NAME_DMP)..."
				$(CC) -o $(NAME_DMP) $(OBJ_DMP)

clean:
				@echo "Deleting nm object files..."
				$(RM) $(OBJ_NM)
				@echo "Deleting objdump object files..."
				$(RM) $(OBJ_DMP)

fclean:			clean
				@echo "Deleting of binary $(NAME_NM)..."
				$(RM) $(NAME_NM)
				@echo "Deleting of binary $(NAME_DMP)..."
				$(RM) $(NAME_DMP)

re:				fclean all

.PHONY:			all nm objdump clean fclean re