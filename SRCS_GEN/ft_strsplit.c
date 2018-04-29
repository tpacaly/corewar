/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:01:11 by tpacaly           #+#    #+#             */
/*   Updated: 2018/04/28 15:01:30 by tpacaly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

char		**ft_strsplit(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**split;

	i = 0;
	k = 0;
	if (!(split = (char **)malloc(sizeof(char *) * 256)))
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i += 1;
	while (str[i])
	{
		j = 0;
		if (!(split[k] = (char *)malloc(sizeof(char) * 4096)))
			return (NULL);
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			split[k][j++] = str[i++];
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i += 1;
		split[k][j] = '\0';
		k += 1;
	}
	split[k] = NULL;
	return (split);
}
