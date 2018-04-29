#include "../includes/corewar.h"

void	exec2(t_vm *env, t_champ *champ, unsigned char commande)
{
	if (commande == 4)
	{
		if (champ->action != NULL)
			add(env, env->arene, champ);
		else
			champ->cycle += 10;
	}
	if (commande == 5)
	{
		if (champ->action != NULL)
			sub(env, env->arene, champ);
		else
			champ->cycle += 10;
	}
	if (commande == 6)
	{
		if (champ->action != NULL)
			and(env->arene, champ);
		else
			champ->cycle += 6;
	}
	exec3(env, champ, commande);
}

void	exec3(t_vm *env, t_champ *champ, unsigned char commande)
{
	if (commande == 7)
	{
		if (champ->action != NULL)
			or(env->arene, champ);
		else
			champ->cycle += 6;
	}
	if (commande == 8)
	{
		if (champ->action != NULL)
			xor(env->arene, champ);
		else
			champ->cycle += 6;
	}
	if (commande == 9)
	{
		if (champ->action != NULL)
			zjump(env, env->arene, champ);
		else
			champ->cycle += 20;
	}
	exec4(env, champ, commande);
}

void	exec4(t_vm *env, t_champ *champ, unsigned char commande)
{
	if (commande == 10)
	{
		if (champ->action != NULL)
			ldi(env->arene, champ);
		else
			champ->cycle += 25;
	}
	if (commande == 11)
	{
		if (champ->action != NULL)
			sti(env->arene, champ);
		else
			champ->cycle += 25;
	}
	if (commande == 12)
	{
		if (champ->action != NULL)
			f_fork(env->arene, champ, env);
		else
			champ->cycle += 800;
	}
	exec5(env, champ, commande);
}

void	exec5(t_vm *env, t_champ *champ, unsigned char commande)
{
	if (commande == 13)
	{
		if (champ->action != NULL)
			lld(env, env->arene, champ);
		else
			champ->cycle += 10;
	}
	if (commande == 14)
	{
		if (champ->action != NULL)
			lldi(env->arene, champ);
		else
			champ->cycle += 50;
	}
	if (commande == 3)
	{
		if (champ->action != NULL)
			st(env, env->arene, champ);
		else
			champ->cycle += 5;
	}
	exec6(env, champ, commande);
}

void	exec6(t_vm *env, t_champ *champ, unsigned char commande)
{
	if (commande == 15)
	{
		if (champ->action != NULL)
			f_lfork(env->arene, champ, env);
		else
			champ->cycle += 1000;
	}
	if (commande == 16)
	{
		if (champ->action != NULL)
			aff(env->arene, champ);
		else
			champ->cycle += 2;
	}
	if (commande == 2)
	{
		if (champ->action != NULL)
			ld(env, env->arene, champ);
		else
			champ->cycle += 5;
	}
}
