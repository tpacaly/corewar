#include "../includes/corewar.h"

void		set_carry(t_champ *champ, t_champ *ref)
{
	while (champ)
	{
		if (champ->id == ref->id)
			champ->carry = (champ->carry == 1) ? 0 : 1;
		champ = champ->next;
	}
}

void		rang(t_vm *env, t_champ *champ)
{
	t_champ	*cur;
	t_champ *prev;

	prev = champ;
	cur = champ->next;
	if (!cur || !prev)
		return ;
	if (cur->cycle >= champ->cycle)
		return ;
	while (cur->next && cur->cycle <= champ->cycle)
	{
		prev = prev->next;
		cur = cur->next;
	}
	env->champ = champ->next;
	if (cur->cycle < champ->cycle)
	{
		champ->next = cur->next;
		cur->next = champ;
		return ;
	}
	champ->next = cur;
	if (prev != champ)
		prev->next = champ;
}

t_champ		*find_by_id(t_vm *env, int id)
{
	t_champ	*cur;

	cur = env->champ;
	while (cur)
	{
		if (cur->id == id)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

short		get_short(unsigned char *read)
{
	unsigned char tmp[2];

	tmp[0] = *(read + 1);
	tmp[1] = *read;
	return (*((short*)(&tmp[0])));
}

int			get_int(unsigned char *read)
{
	unsigned char tmp[4];

	tmp[0] = *(read + 3);
	tmp[1] = *(read + 2);
	tmp[2] = *(read + 1);
	tmp[3] = *read;
	return (*((int*)(&tmp[0])));
}
