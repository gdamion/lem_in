/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:42:42 by gdamion-          #+#    #+#             */
/*   Updated: 2019/07/21 14:32:12 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t		row_count(char **table)
{
	size_t	size;

	size = 0;
	if (table)
	{
		while (*table)
		{
			size++;
			table++;
		}
	}
	return (size);
}

_Bool		valid_name(char *str)
{
	if (str && ft_strlen(str))
	{
		if (str[0] != 'L' && str[0] != '#')
			return (TRUE);
	}
	return (FALSE);
}

void		init_lem(void)
{
	if (INIT_LEM_IN)
		project_free(ERR_LEM_IN_INIT, 0);
	ft_bzero(g_lem_in, sizeof(t_lem_in));
	g_lem_in->start = -1;
	g_lem_in->end = -1;
}

_Bool		**init_matrix(int rooms)
{
	int		a;
	_Bool	**matrix;

	a = 0;
	if (!(matrix = (_Bool**)malloc(sizeof(_Bool*) * rooms)))
		project_free(ERR_LINE_INIT, 0);
	while (a < rooms)
	{
		if (!(matrix[a] = (_Bool*)malloc(sizeof(_Bool) * rooms)))
		{
			while (--a >= 0)
				free(matrix[a]);
			project_free(ERR_MATRIX_INIT, 0);
		}
		ft_bzero(matrix[a], sizeof(char) * rooms);
		a++;
	}
	return (matrix);
}

void		output(t_lst **data)
{
	t_lst	*temp;

	while ((*data)->next)
		(*data) = (*data)->next;
	while ((*data))
	{
		ft_printf("%s\n", (*data)->line);
		ft_strdel(&((*data)->line));
		temp = (*data);
		(*data) = (*data)->prev;
		free(temp);
	}
	ft_printf("\n");
}
