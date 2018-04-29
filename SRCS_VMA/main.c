#include "../includes/corewar.h"

void	ft_vm_error(char *error)
{
	ft_put(error, ft_strlen(error) - 1, 2, 0);
	exit(0);
}

void	crawler(t_vm *env)
{
	t_champ						*champ;
	int							activity;
	static unsigned long long	cycle = 0;
	unsigned long long			maxcycle;

	maxcycle = env->nbr_cycles;
	while (cycle < maxcycle)
	{
		activity = 0;
		champ = env->champ;
		while (champ && cycle >= champ->cycle)
		{
			activity += 1;
			exec(env, champ);
			if (champ->next)
				champ = champ->next;
			else
				champ = env->champ;
			if (champ->cycle >= cycle && env->champ->cycle <= cycle)
				champ = env->champ;
		}
		cycle += 1;
		if (cycle >= maxcycle)
			maxcycle += check_live(env);
	}
}

void	passive_check(int ac)
{
	if (ac < 2)
		ft_vm_error("ERROR d'argument\n");
	if (CYCLE_TO_DIE < 1 || CYCLE_DELTA < 1 || IND_SIZE != 2 || REG_SIZE != 4)
		ft_vm_error("ERROR de variables d'environnement\n");
}

int		is_num_in_list(t_champ *champ, int n)
{
	champ = champ->next;
	while(champ)
	{
		if(champ->id == n)
			return(1);
		champ = champ->next;
	}
	return(0);
}

void	organise_num(t_champ *champ)
{
	t_champ *act;

	act = champ;
	while(champ)
	{
		if(is_num_in_list(champ, champ->id) == 1)
		{
			champ->id = (champ->id > 8) ? 1 : champ->id + 1;
			champ = act;
		}
		else
			champ = champ->next;
	}
}

void	print_ids(t_champ *champ)
{
	int i;

	i = 0;
	while(champ)
	{
		printf("%d %d\n", i, champ->id);
		i++;
		champ = champ->next;
	}
}

t_champ	*champions(int cur, t_champ *champ, char **av, int ac)
{
	t_champ *target;
	int i;

	target = NULL;
	i = 0;
	while (cur < ac)
	{
		if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
			ft_vm_error("ERROR de malloc sur les champions\n");
		champ->id = put_name(&cur, av);
		if (cur >= ac)
			ft_vm_error("ERROR d'argument\n");
		champ->action = NULL;
		if ((champ->fd = open(av[cur], O_RDONLY)) < 0)
			ft_vm_error("ERROR d'ouverture des fichier\n");
		ft_memset(champ->registre, 0, REG_SIZE * REG_NUMBER);
		cur++;
		champ->next = target;
		target = champ;
		champ = NULL;
		i++;
		if(i > MAX_PLAYERS)
			ft_vm_error("ERROR, too many players.\n");
	}
	organise_num(target);
	return (target);
}

int		main(int ac, char **av)
{
	int		cur;
	t_vm	env;
	t_champ	*champ;

	passive_check(ac);
	cur = 1;
	champ = NULL;
	if (ft_strcmp(av[1], "-dump") == 0 && av[2])
	{
		env.nbr_cycles = ft_atoi(av[2]);
		cur += 2;
	}
	else
		env.nbr_cycles = CYCLE_TO_DIE;
	if (env.nbr_cycles <= 0 || cur >= ac || av[2])
		ft_vm_error("ERROR d'argument\n");
	env.champ = champions(cur, champ, av, ac);
	make_arene(&env);
	crawler(&env);
	if (env.winn)
		ft_put(env.winn, ft_strlen(env.winn) - 1, 1, 1);
	else
		ft_put("No one", 6, 1, 0);
	ft_put(" Win !\n", 7, 1, 0);
	ft_free_all_vm(&env);
	return (0);
}
