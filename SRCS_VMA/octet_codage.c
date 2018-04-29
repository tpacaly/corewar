#include "../includes/corewar.h"

int	ft_free_all_vm(t_vm *env)
{
	t_champ *h;
	t_champ *g;

	h = env->champ;
	while (h)
	{
		g = h->next;
		ft_memdel((void **)&h);
		h = g;
	}
	ft_strdel((char **)&env->arene);
	return (0);
}

static	int	third_place(char target, char place, unsigned char value)
{
	if (value >= 12 && target == 3 && place == 3)
		return (1);
	else if (value >= 8 && target == 2 && place == 3)
		return (1);
	else if (value < 8 && target == 1 && place == 3)
		return (1);
	return (0);
}

static	int	second_place(char target, char place, unsigned char value)
{
	if (value >= 48 && target == 3 && place == 2)
		return (1);
	else if (value >= 32 && target == 2 && place == 2)
		return (1);
	else if (value < 32 && target == 1 && place == 2)
		return (1);
	if (value >= 32)
		value -= 32;
	if (value >= 16)
		value -= 16;
	return (third_place(target, place, value));
}

int			oct_codage(char target, char place, unsigned char value)
{
	if (value >= 192 && target == 3 && place == 1)
		return (1);
	else if (value >= 128 && target == 2 && place == 1)
		return (1);
	else if (value < 128 && target == 1 && place == 1)
		return (1);
	if (value >= 128)
		value -= 128;
	if (value >= 64)
		value -= 64;
	return (second_place(target, place, value));
}
