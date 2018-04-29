#include "../includes/corewar.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int index;

	index = 0;
	while (s1[index] && s2[index] && s1[index] == s2[index])
		index++;
	return (s1[index] - s2[index]);
}
