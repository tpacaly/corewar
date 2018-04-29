#include "../includes/corewar.h"

/*
** cur->live est une booleen a 1 si le champion est en vie
*/

static int	extend(t_champ **prev, t_champ **cur, t_vm *env)
{
	t_champ *tmp;

	tmp = NULL;
	if (*prev)
		(*prev)->next = (*cur)->next;
	else
	{
		env->champ = (*cur)->next;
		tmp = *cur;
		(*cur) = (*cur)->next;
		ft_memdel((void**)&tmp);
		return (2);
	}
	ft_memdel((void**)cur);
	*cur = NULL;
	(*cur) = (*prev);
	(*prev) = NULL;
	return (1);
}

void		give_live(t_champ *champ, int id, t_vm *env)
{
	static int	boo = 0;
	t_champ		*cur;

	cur = champ;
	while (cur)
	{
		if (cur->id == id)
		{
			if (boo == 1)
				ft_strdel((char**)&env->winn);
			boo = 1;
			env->winn = ft_strdup(champ->head.prog_name);
			cur->live = 1;
		}
		cur = cur->next;
	}
}

int			check(t_champ *champ)
{
	t_champ	*cur;

	cur = champ;
	while (cur)
	{
		if (champ->id != cur->id)
			return (1);
		cur->live = 0;
		cur = cur->next;
	}
	return (0);
}

long		check_live(t_vm *env)
{
	t_champ							*cur;
	t_champ							*prev;
	static unsigned long			die = CYCLE_TO_DIE;
	static unsigned long			eck = 0;

	if (eck == 0)
		die = env->nbr_cycles;
	eck += 5;
	cur = env->champ;
	prev = NULL;
	while (cur && eck < 10000)
	{
		if (cur->live != 1)
			eck = extend(&prev, &cur, env);
		prev = cur;
		if (eck != 2)
			cur = cur->next;
		eck += 5;
	}
	die -= CYCLE_DELTA;
	if (check(env->champ) == 0 || die <= 0)
		return (0);
	return (die);
}
