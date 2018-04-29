#include "../includes/corewar.h"

int				magic_check(unsigned int m1, unsigned int m2)
{
	unsigned char	*cur1;
	unsigned char	*cur2;

	cur1 = (unsigned char*)&m1 + 3;
	cur2 = (unsigned char*)&m2;
	while (*cur1 == 0)
		cur1 -= 1;
	while (*cur2 == 0)
		cur2 += 1;
	while (*cur2)
	{
		if (*cur1 != *cur2)
			return (-1);
		cur1 -= 1;
		cur2 += 1;
	}
	return (0);
}

unsigned int	inv_uint(unsigned int target)
{
	char	*cur;
	char	tmp;

	cur = (char*)&target;
	tmp = cur[3];
	cur[3] = cur[0];
	cur[0] = tmp;
	tmp = cur[2];
	cur[2] = cur[1];
	cur[1] = tmp;
	return (target);
}

void			make_player(t_vm *env, int nbr)
{
	int				max_size;
	static int		cur;
	long			tmp;
	t_champ			*champ;

	max_size = MEM_SIZE / nbr;
	champ = env->champ;
	cur = 0;
	while (champ)
	{
		if (read(champ->fd, &champ->head, sizeof(t_header)) <= 0)
			ft_vm_error("ERROR: incorect file\n");
		if (magic_check(COREWAR_EXEC_MAGIC, champ->head.magic) != 0)
			ft_vm_error("ERROR: incorect magic number\n");
		champ->head.prog_size = inv_uint(champ->head.prog_size);
		if (read(champ->fd, &env->arene[cur * max_size], champ->head.prog_size \
		+ 5) != champ->head.prog_size || champ->head.prog_size > CHAMP_MAX_SIZE || champ->head.prog_size < CHAMP_MIN_SIZE)
			ft_vm_error("ERROR: incorect file\n");
		champ->pc = cur * max_size;
		tmp = -champ->id;
		tmp = get_int((unsigned char*)&tmp);
		ft_memcpy(&champ->registre[REG_SIZE], &tmp, 4);
		cur++;
		champ = champ->next;
	}
}

void			make_arene(t_vm *env)
{
	t_champ	*cur;
	int		nbr;

	if (!(env->arene = (unsigned char*)malloc(MEM_SIZE)))
		ft_vm_error("ERROR de malloc pour l'arene\n");
	ft_memset(env->arene, 0, MEM_SIZE);
	cur = env->champ;
	nbr = 0;
	while (cur)
	{
		cur = cur->next;
		nbr++;
	}
	make_player(env, nbr);
}

int				put_name(int *cur, char **av)
{
	static int	name = 0;

	if (ft_strcmp(av[*cur], "-n") == 0)
	{
		*cur += 1;
		if (av[*cur][0] < (char)'0' || av[*cur][0] > (char)'9')
			ft_vm_error("ERROR de format de la commande\n");
		*cur += 1;
		return (ft_atoi(av[*cur - 1]));
	}
	else
	{
		name++;
		return (name);
	}
}
