/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpacaly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:21:01 by tpacaly           #+#    #+#             */
/*   Updated: 2018/04/28 10:58:36 by tpacaly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int				ft_free_all(t_asm *strukt)
{
	int		index;
	char	**tab_file;

	tab_file = strukt->tab_label;
	index = -1;
	if(tab_file != 0)
	{
		while (tab_file[++index])
			ft_strdel(&tab_file[index]);
		free((void**)tab_file);
	}
	tab_file = strukt->file;
	index = -1;
	while (tab_file[++index])
		ft_strdel(&tab_file[index]);
	free((void**)tab_file);
	ft_strdel(&strukt->file_s_name);
	(strukt->path != NULL) ? ft_strdel(&strukt->path) : 0;
	return (0);
}

int				ft_print_file(t_asm *strukt)
{
	char	**tab_file;
	int		index;

	index = -1;
	tab_file = strukt->file;
	while (tab_file[++index])
		ft_put(tab_file[index], '\n', 1, 0);
	ft_free_all(strukt);
	ft_memdel((void**)&strukt);
	return (0);
}

static char		*ft_trunc_name(t_asm *strukt)
{
	int		index;
	char	*name_trunc;

	index = -1;
	while (strukt->file_s_name[++index])
		;
	while (strukt->file_s_name[index] != '.')
		index--	;
	strukt->file_s_name[index] = '\0';
	if (!(name_trunc = (char *)malloc(sizeof(char) * index + 1)))
		ft_exit("Malloc failed in create_file_core.c");
	name_trunc[index] = 0;
	index = -1;
	while (strukt->file_s_name[++index])
		name_trunc[index] = strukt->file_s_name[index];
	return (name_trunc);
}

t_asm			*ft_create_file_cor(t_asm *strukt)
{
	strukt->path = ft_strjoin_set(ft_trunc_name(strukt), ".cor", 1);
	if (!(strukt->fd_cor =
		open(strukt->path, O_TRUNC | O_RDWR | O_CREAT, 0777 | O_APPEND)))
		ft_error(8, NULL);
	return (strukt);
}
