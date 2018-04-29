#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

# define RED	"\x1b[31m"
# define GRN	"\x1b[32m"
# define YEL	"\x1b[33m"
# define BLU	"\x1b[34m"
# define MAG	"\x1b[35m"
# define CYA	"\x1b[36m"
# define RES	"\x1b[0m"

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define REG_NUMBER				16
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define CHAMP_MIN_SIZE			PROG_NAME_LENGTH + 8 + COMMENT_LENGTH + 4

# define CYCLE_TO_DIE			1500
# define CYCLE_DELTA			1150

# define COREWAR_EXEC_MAGIC		0xea83f3
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define BUFF_SIZE (CHAMP_MAX_SIZE)

typedef struct			s_list
{
	char				*str;
	struct s_list		*first;
	struct s_list		*next;
}						t_list;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_asm
{
	int					a;
	int					b;
	int					h;
	int					ac;
	int					first;
	char				**av;
	char				**file;
	char				**tab_label;
	char				bool_name;
	char				bool_comment;
	char				bool_header;
	char				*file_s_name;
	char				*ins;
	unsigned int		size;
	char				*path;
	int					fd_cor;
	t_list				*list;
	t_header			header;
}						t_asm;

typedef struct			s_ins
{
	unsigned short		tmp;
	unsigned int		tp;
	int					i;
	unsigned char		inst;
}						t_ins;

void					ft_write(t_asm *strukt, const void *tmp, size_t len);
void					ft_aff(t_asm *s_asm, char *s);
void					ft_zjmp(t_asm *s_asm, char *s, int line);
void					ft_fork(t_asm *s_asm, char *s, int line);
void					ft_live(t_asm *s_asm, char *s, int line);
void					ft_lfork(t_asm *s_asm, char *s, int line);
void					ft_st(t_asm *s_asm, char *s, char opcode, int line);
void					ft_sti(t_asm *s_asm, char *s, char opcode, int line);
void					ft_ld_lld(t_asm *s_asm, char *s, char \
						opcode, int line);
void					ft_ldi_lldi(t_asm *s_asm, char *s, \
						char opcode, int line);
void					ft_sub_add(t_asm *s_asm, char *s, char opcode);
void					ft_and_xor_or(t_asm *s_asm, char *s, \
						char opcode, int line);
void					ft_error(size_t id_error, char *name);
int						ft_print_file(t_asm *strukt);
int						ft_free_all(t_asm *strukt);
t_asm					*ft_check_file_s(t_asm *s_asm);
void					ft_open_check_and_get_file(t_asm *s_asm);
t_asm					*ft_create_file_cor(t_asm *s_asm);
void					ft_write_magic_number(t_asm *s_asm);
void					ft_write_name(t_asm *s_asm);
void					ft_write_prog_size(t_asm *s_asm);
void					ft_write_comment(t_asm *s_asm);
void					ft_check_asm(t_asm *s_asm, int index);
void					ft_write_instructions(t_asm *s_asm);
t_list					*ft_linked_list_str(t_list *list, \
						char *str, char to_free);
unsigned int			ft_find_label(t_asm *strukt, char *s, int actual);
void					ft_op_dir(char *s, char *bool_op, char *bool_dir);
char					*ft_strjoin_set(char *s1, char *s2, char setting);
int						ft_find_line(t_asm *s_asm, char *s, int k, int line);
int						ft_count(char *s, char t_dir, int i);
void					ft_write_ui(unsigned int value, t_asm *s_asm);
void					ft_write_us(unsigned short value, t_asm *s_asm);
int						ft_find_instruction(char *s);
unsigned char			ft_write_codage(char *s);
void					ft_check_header(void);
void					ft_exit(char *str);
void					ft_exit_and_destroy(t_asm *s_asm, char *str);
void					ft_check_instruction_line(char *s, char \
	nbr, char *inst);
char					ft_is_r(char *s, char *nbr, char *inst, int *index);
char					ft_is_ind(char *s, char *nbr, char *inst, int *index);
char					ft_is_label(char *s, char *nbr, char *inst, int *index);

typedef struct			s_champ
{
	int					id;
	t_header			head;
	int					fd;
	unsigned char		*action;
	unsigned long long	cycle;
	unsigned long long	pc;
	char				carry;
	char				live;
	unsigned char		registre[REG_SIZE * REG_NUMBER];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_vm
{
	long				nbr_cycles;
	int					winner;
	char				*winn;
	t_champ				*champ;
	unsigned char		*arene;
}						t_vm;

void					ft_vm_error(char *error);
long					check_live(t_vm *env);
int						put_name(int *cur, char **av);
void					make_arene(t_vm *env);
void					make_player(t_vm *env, int nbr);
void					rang(t_vm *env, t_champ *champ);
void					set_carry(t_champ *champ, t_champ *ref);
void					give_live(t_champ *champ, int id, t_vm *env);
void					exec(t_vm *env, t_champ *champ);
void					exec2(t_vm *env, t_champ *champ, unsigned char \
						commande);
void					exec3(t_vm *env, t_champ *champ, unsigned char \
						commande);
void					exec4(t_vm *env, t_champ *champ, unsigned char \
						commande);
void					exec5(t_vm *env, t_champ *champ, unsigned char \
						commande);
void					exec6(t_vm *env, t_champ *champ, unsigned char \
						commande);
short					get_short(unsigned char *read);
int						get_int(unsigned char *read);
short					get_short2(void *read);
int						get_int2(unsigned char *read);
int						oct_codage(char target, char place, unsigned char \
						value);
void					live(unsigned char *arene, t_champ *champ, t_vm *env);
void					ld(t_vm *env, unsigned char *arene, t_champ *champ);
void					st(t_vm *env, unsigned char *arene, t_champ *champ);
void					add(t_vm *env, unsigned char *arene, t_champ *champ);
void					sub(t_vm *env, unsigned char *arene, t_champ *champ);
void					and(unsigned char *arene, t_champ *champ);
void					or(unsigned char *arene, t_champ *champ);
void					xor(unsigned char *arene, t_champ *champ);
void					zjump(t_vm *env, unsigned char *arene, t_champ *champ);
void					ldi(unsigned char *arene, t_champ *champ);
void					sti(unsigned char *arene, t_champ *champ);
void					f_fork(unsigned char *arene, t_champ *champ, \
						t_vm *env);
void					lld(t_vm *env, unsigned char *arene, t_champ *champ);
void					lldi(unsigned char *arene, t_champ *champ);
void					f_lfork(unsigned char *arene, t_champ *champ, \
						t_vm *env);
void					aff(unsigned char *arene, t_champ *champ);
int						ft_free_all_vm(t_vm *env);

void					ft_strdel(char **as);
void					ft_put(char *str, char c, char fd, char bool_free);
size_t					ft_strlen(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
void					*ft_memmove(void *dst, const void *src, size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *src);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strsub(char const *s, unsigned int \
						start, size_t len);
void					ft_memdel(void **ap);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_memdup(const void *restrict src, size_t n);
void					*ft_memcpy(void *restrict dst, const void \
						*restrict src, size_t n);
char					*ft_itoa(int n);
int						ft_atoi(const char *str);
int						get_next_line(int const fd, char **line);
char					**ft_malloc_tabtab(char **tab, char *str);
char					*ft_strchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strndup(const char *s, size_t n);
char					**ft_strsplit(char *str);
char					*ft_strdup(const char *src);
char					*ft_itoa_base(int value, int base);

#endif
