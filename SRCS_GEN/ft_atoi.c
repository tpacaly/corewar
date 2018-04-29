int			ft_atoi(const char *str)
{
	char	*cursor;
	int		result;
	int		neg;

	neg = 1;
	cursor = (char *)str;
	result = 0;
	while ((*cursor <= (char)13 && *cursor >= (char)9) || *cursor == (char)32)
		cursor++;
	if (*cursor == '-' || *cursor == '+')
	{
		if (*cursor == '-')
			neg = -1;
		cursor++;
	}
	while (*cursor >= '0' && *cursor <= '9')
	{
		result *= 10;
		result += *cursor - 48;
		cursor++;
	}
	return (result * neg);
}
