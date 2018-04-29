#include "../includes/corewar.h"

void	sub(t_vm *env, unsigned char *arene, t_champ *champ)
{
	champ->pc += 1;
	champ->registre[arene[(champ->pc + 2) % MEM_SIZE] * REG_SIZE] = \
	champ->registre[arene[(champ->pc + 1) % MEM_SIZE] * REG_SIZE] - \
	champ->registre[arene[champ->pc % MEM_SIZE] * REG_SIZE];
	set_carry(env->champ, champ);
	champ->pc += 3;
}

void	aff(unsigned char *arene, t_champ *champ)
{
	champ->pc += 1;
	ft_put((char*)&arene[champ->pc % MEM_SIZE], 1, 1, 0);
	champ->pc += 1;
}

void	f_fork(unsigned char *arene, t_champ *champ, t_vm *env)
{
	long			refn;
	short			target;
	t_champ			*new;

	refn = champ->pc - 1;
	target = get_short(&arene[champ->pc % MEM_SIZE]);
	new = (t_champ*)malloc(sizeof(t_champ));
	new->action = NULL;
	new->next = env->champ;
	new->pc = refn + (target % IDX_MOD);
	new->id = champ->id;
	ft_memcpy(new->registre, champ->registre, REG_SIZE * REG_NUMBER);
	new->carry = champ->carry;
	new->cycle = champ->cycle;
	new->head = champ->head;
	env->champ = new;
	rang(env, new);
	champ->pc += 2;
}

void	lld(t_vm *env, unsigned char *arene, t_champ *champ)
{
	int					val;
	short				val2;
	unsigned long long	ref;

	ref = champ->pc - 1;
	champ->pc += 1;
	if (oct_codage(3, 1, arene[(champ->pc - 1) % MEM_SIZE]) == 1)
	{
		val2 = get_short(&arene[(champ->pc) % MEM_SIZE]);
		champ->pc += 2;
		ft_memcpy(&champ->registre[(arene[champ->pc] % REG_NUMBER) * REG_SIZE],\
		&arene[(ref + val2) % MEM_SIZE], REG_SIZE);
	}
	else
	{
		val = get_int(&arene[champ->pc % MEM_SIZE]);
		val = get_int(&arene[(ref + val) % MEM_SIZE]);
		champ->pc += 4;
		ft_memcpy(&champ->registre[(arene[champ->pc] % REG_NUMBER) * REG_SIZE],\
		&arene[(ref + val) % MEM_SIZE], REG_SIZE);
	}
	champ->pc += 1;
	set_carry(env->champ, champ);
}

void	zjump(t_vm *env, unsigned char *arene, t_champ *champ)
{
	short	value;

	value = get_short(&arene[champ->pc % MEM_SIZE]);
	if (champ->carry == 1)
		champ->pc = champ->pc - 1 + value;
	else
	{
		champ->pc += 2;
		set_carry(env->champ, champ);
	}
}
