FLAGS = -Wall -Wextra -Werror

NAME_VMA = 	corewar

SRCS_GEN =	SRCS_GEN/put.c							\
			SRCS_GEN/strcmp.c						\
			SRCS_GEN/strlen.c						\
			SRCS_GEN/strdup.c						\
			SRCS_GEN/strchr.c						\
			SRCS_GEN/strsub.c						\
			SRCS_GEN/strdel.c						\
			SRCS_GEN/memdel.c						\
			SRCS_GEN/strndup.c						\
			SRCS_GEN/strncmp.c						\
			SRCS_GEN/strjoin.c						\
			SRCS_GEN/memmove.c						\
			SRCS_GEN/get_next_line.c				\
			SRCS_GEN/malloc_tabtab.c				\
			SRCS_GEN/ft_atoi.c						\
			SRCS_GEN/ft_memcpy.c					\
			SRCS_GEN/ft_strsplit.c \
			SRCS_GEN/ft_itoa_base.c \
			SRCS_GEN/ft_memset.c					

OBJ_GEN =	$(SRCS_GEN:.c=.o)	

SRCS_VMA  = SRCS_VMA/main.c							\
			SRCS_VMA/champ_tool.c					\
			SRCS_VMA/exec.c							\
			SRCS_VMA/exec2.c						\
			SRCS_VMA/fonc.c							\
			SRCS_VMA/fonc2.c						\
			SRCS_VMA/fonc3.c						\
			SRCS_VMA/fonc4.c						\
			SRCS_VMA/fonc5.c						\
			SRCS_VMA/live_tool.c					\
			SRCS_VMA/make.c							\
			SRCS_VMA/octet_codage.c					\
			$(SRCS_GEN)

OBJ_VMA =	$(SRCS_VMA:.c=.o)

NAME_ASM = 	asm

SRCS_ASM  = SRCS_ASM/utils.c \
			SRCS_ASM/errors.c \
			SRCS_ASM/ins.c \
			SRCS_ASM/ins2.c \
			SRCS_ASM/ins3.c \
			SRCS_ASM/ins4.c \
			SRCS_ASM/ins5.c \
			SRCS_ASM/ins6.c \
			SRCS_ASM/ins7.c \
			SRCS_ASM/ins8.c \
			SRCS_ASM/ft_opdir.c \
			SRCS_ASM/ft_label.c \
			SRCS_ASM/ft_label2.c \
			SRCS_ASM/write.c \
			SRCS_ASM/check_head.c \
			SRCS_ASM/check_ins.c \
			SRCS_ASM/check_ins2.c \
			SRCS_ASM/check_filedots.c \
			SRCS_ASM/check_code.c \
			SRCS_ASM/main.c \
			$(SRCS_GEN)

OBJ_ASM = $(SRCS_ASM:.c=.o)
OBJ_VMA = $(SRCS_VMA:.c=.o)

all: $(NAME_ASM) $(NAME_VMA)

WORK:	$(OBJ_GEN)
	@ echo "🚧  \033[33mWORK IN PROGRESS\033[0m 🚧"

$(NAME_ASM): WORK $(OBJ_ASM)
	@gcc $(FLAG) -o $(NAME_ASM) $(OBJ_ASM)
	@ echo "Compilation \033[36mASM\033[0m: [\033[32mcompleted\033[0m]"

$(NAME_VMA): WORK $(OBJ_VMA)
	@gcc $(FLAG) -o $(NAME_VMA) $(OBJ_VMA)
	@ echo "Compilation \033[36mVM\033[0m: [\033[32mcompleted\033[0m]"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $^

clean:
	@rm -f $(OBJ_ASM)
	@rm -f $(OBJ_VMA)

fclean: clean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_VMA)

re : fclean all

.PHONY: all, clean, fclean, re, WORK
