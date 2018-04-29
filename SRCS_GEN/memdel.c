#include "../includes/corewar.h"

void	ft_memdel(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}
