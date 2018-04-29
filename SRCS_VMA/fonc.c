#include "../includes/corewar.h"

/*
** Les commandes du champions une par une
*/

void	live(unsigned char *arene, t_champ *champ, t_vm *env)
{
	int		tp;

	tp = (get_int(&arene[champ->pc]) > 0) ? get_int(&arene[champ->pc]) : -1 * \
	get_int(&arene[champ->pc % MEM_SIZE]);
	env->winner = tp;
	give_live(env->champ, tp, env);
	champ->pc += 4;
}

void	ld(t_vm *env, unsigned char *arene, t_champ *champ)
{
	int					val;
	short				val2;
	unsigned long long	ref;

	ref = champ->pc - 1;
	if (oct_codage(3, 1, arene[champ->pc]) == 1)
	{
		champ->pc += 1;
		val2 = get_short(&arene[champ->pc % MEM_SIZE]);
		champ->pc += 2;
		ft_memcpy(&champ->registre[REG_SIZE * (arene[champ->pc]) % REG_NUMBER]\
		, &arene[(ref + (val2 % IDX_MOD)) % MEM_SIZE], REG_SIZE);
	}
	else
	{
		val = get_int(&arene[(champ->pc + 1) % MEM_SIZE]);
		val = get_int(&arene[(ref + val) % MEM_SIZE]);
		champ->pc += 5;
		ft_memcpy(&champ->registre[arene[champ->pc] * REG_SIZE], &arene[(ref \
			+ (val % IDX_MOD)) % MEM_SIZE], REG_SIZE);
	}
	set_carry(env->champ, champ);
	champ->pc += 1;
}

void	st(t_vm *env, unsigned char *arene, t_champ *champ)
{
	unsigned char	*reg;

	if (oct_codage(1, 2, arene[champ->pc]) == 1)
	{
		champ->pc += 1;
		reg = &champ->registre[REG_SIZE * (arene[champ->pc] % REG_NUMBER)];
		champ->pc += 1;
		ft_memcpy(&champ->registre[(REG_SIZE * arene[champ->pc]) % (REG_SIZE * \
			REG_NUMBER)], reg, REG_SIZE);
	}
	else
	{
		champ->pc += 1;
		reg = &champ->registre[REG_SIZE * (arene[champ->pc] % REG_NUMBER)];
		champ->pc += 1;
		ft_memcpy(&arene[champ->pc - 3 + get_short(&arene[champ->pc]) % \
		MEM_SIZE], reg, REG_SIZE);
		champ->pc += 1;
	}
	set_carry(env->champ, champ);
	champ->pc += 1;
}

void	add(t_vm *env, unsigned char *arene, t_champ *champ)
{
	champ->pc += 1;
	champ->registre[(arene[champ->pc + 2] % REG_NUMBER) * REG_SIZE] = \
	champ->registre[(arene[champ->pc + 1] % REG_NUMBER) * REG_SIZE] + \
	champ->registre[(arene[champ->pc] % REG_NUMBER) * REG_SIZE];
	set_carry(env->champ, champ);
	champ->pc += 3;
}

void	f_lfork(unsigned char *arene, t_champ *champ, t_vm *env)
{
	long			refn;
	short			target;
	t_champ			*new;

	refn = champ->pc - 1;
	target = get_short(&arene[champ->pc]);
	new = (t_champ*)malloc(sizeof(t_champ));
	new->action = NULL;
	new->next = env->champ;
	new->pc = refn + target;
	new->id = champ->id;
	ft_memcpy(new->registre, champ->registre, REG_SIZE * REG_NUMBER);
	new->carry = champ->carry;
	new->cycle = champ->cycle;
	new->head = champ->head;
	rang(env, new);
	champ->pc += 2;
}
