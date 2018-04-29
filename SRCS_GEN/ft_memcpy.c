#include <stdlib.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*cursor;
	unsigned char	*copiter;
	unsigned char	*mem;

	mem = (unsigned char *)dst;
	if (n == 0)
		return (dst);
	cursor = (unsigned char *)dst;
	copiter = (unsigned char *)src;
	while (n--)
	{
		*cursor = *copiter;
		copiter++;
		cursor++;
	}
	return (mem);
}

void	*ft_memdup(const void *restrict src, size_t n)
{
	unsigned char	*cursor;
	unsigned char	*copiter;
	unsigned char	*dst;
	unsigned char	*mem;

	dst = (unsigned char*)malloc(n * sizeof(unsigned char));
	mem = (unsigned char *)dst;
	if (n == 0)
		return (dst);
	cursor = (unsigned char *)dst;
	copiter = (unsigned char *)src;
	while (n--)
	{
		*cursor = *copiter;
		copiter++;
		cursor++;
	}
	return (mem);
}
