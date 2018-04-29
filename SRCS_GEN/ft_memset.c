#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cursor;

	if (len == 0)
		return (b);
	cursor = (unsigned char *)b;
	while (len > 0)
	{
		*cursor = (unsigned char)c;
		if (len)
			cursor++;
		len--;
	}
	return (b);
}
