#include "../includes/corewar.h"

static int	xor2(unsigned char *arene, t_champ *champ, unsigned char ref)
{
	champ->pc += 1;
	if (oct_codage(1, 1, ref) == 1)
	{
		champ->pc += 1;
		return (champ->registre[arene[(champ->pc - 1) % MEM_SIZE] * REG_SIZE]);
	}
	else if (oct_codage(3, 1, ref) == 1)
	{
		champ->pc += 2;
		return (get_short(&arene[(champ->pc - 1) % MEM_SIZE]));
	}
	champ->pc += 4;
	return (get_int(&arene[champ->pc - 6 + get_int(&arene[(champ->pc - 4) % \
			MEM_SIZE])]));
}

void		xor(unsigned char *arene, t_champ *champ)
{
	int				val;
	int				val2;
	int				refn;
	unsigned char	ref;

	ref = arene[champ->pc % MEM_SIZE];
	refn = champ->pc - 1;
	val2 = 0;
	val = xor2(arene, champ, ref);
	if (oct_codage(1, 2, ref) == 1)
		val2 = champ->registre[(arene[champ->pc % MEM_SIZE] % REG_NUMBER) \
		* REG_SIZE];
	else if (oct_codage(3, 2, ref) == 1)
	{
		val2 = get_short(&arene[champ->pc % MEM_SIZE]);
		champ->pc += 1;
	}
	else
	{
		val = get_int(&arene[refn + get_int(&arene[champ->pc % MEM_SIZE])]);
		champ->pc += 3;
	}
	val = val ^ val2;
	ft_memcpy(&(champ->registre[REG_SIZE * arene[(champ->pc - 1) % MEM_SIZE]]),\
	(char*)(&val), 4);
	champ->pc += 2;
}

static int	ldi2(unsigned char *arene, t_champ *champ, unsigned char ref, \
	long refn)
{
	int	val;

	champ->pc += 1;
	if (oct_codage(1, 1, ref) == 1)
	{
		champ->pc += 1;
		return (get_int(&champ->registre[(arene[(champ->pc - 1) % MEM_SIZE] % \
		REG_NUMBER) * REG_SIZE]));
	}
	champ->pc += 2;
	val = get_short(&champ->registre[(arene[(champ->pc - 2) % MEM_SIZE] % \
	REG_NUMBER) * REG_SIZE]);
	if (oct_codage(2, 1, ref) == 1)
		val = get_short(&arene[(refn + (val % IDX_MOD)) % MEM_SIZE]);
	return (val);
}

void		ldi(unsigned char *arene, t_champ *champ)
{
	unsigned char	ref;
	long			refn;
	int				val;
	int				val2;

	ref = arene[champ->pc];
	refn = champ->pc - 1;
	val = ldi2(arene, champ, ref, refn);
	if (oct_codage(1, 2, ref) == 1)
		val2 = champ->registre[(arene[champ->pc] % REG_NUMBER) * REG_SIZE];
	else
	{
		val2 = get_short(&champ->registre[(arene[champ->pc % MEM_SIZE] % \
			REG_NUMBER) * REG_SIZE]);
		val2 = get_short(&arene[(refn + (val2 % IDX_MOD)) % MEM_SIZE]);
		champ->pc += 1;
	}
	champ->pc += 1;
	ft_memcpy(&champ->registre[(arene[champ->pc] % REG_NUMBER) * REG_SIZE], \
	&arene[(val + val2) % MEM_SIZE], REG_SIZE);
	champ->pc += 1;
}
