#include "../includes/corewar.h"

char	*ft_strchr(const char *s, int c)
{
	int index;

	index = 0;
	while (s[index] != '\0' && (s[index] != c))
		index++;
	if (s[index] == c)
		return ((char *)s + index);
	else
		return (NULL);
}
