#include "../includes/corewar.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		index;

	index = 0;
	while (src[index])
		index++;
	str = (char *)malloc(sizeof(*str) * index + 1);
	if (str == NULL)
		return (NULL);
	index = 0;
	while (src[index] != '\0')
	{
		str[index] = src[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
