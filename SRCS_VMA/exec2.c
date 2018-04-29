#include "../includes/corewar.h"

void	exec(t_vm *env, t_champ *champ)
{
	unsigned char commande;

	commande = env->arene[champ->pc];
	champ->pc += 1;
	champ->pc = champ->pc % MEM_SIZE;
	if (commande == 1)
	{
		if (champ->action != NULL)
			live(env->arene, champ, env);
		else
			champ->cycle += 10;
	}
	exec2(env, champ, commande);
	if (commande > 16 || commande == 0)
		champ->cycle += 1;
	if (champ->action == NULL && commande <= 16 && commande != 0)
	{
		champ->pc -= 1;
		champ->action = &env->arene[champ->pc];
	}
	else if (champ->action != NULL)
		champ->action = NULL;
	rang(env, env->champ);
	champ->pc = champ->pc % MEM_SIZE;
}
