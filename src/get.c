/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:43:07 by gdamion-          #+#    #+#             */
/*   Updated: 2019/06/30 17:00:43 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		mark_matrix(char **table, _Bool **matrix, char **names)
{
	int	i;
	int	end;
	int	start;

	i = 0;
	end = -1;
	start = -1;
	while ((start == -1 || end == -1) && names[i])
	{
		if (!ft_strcmp(table[0], names[i]))
			start = i;
		if (!ft_strcmp(table[1], names[i]))
			end = i;
		i++;
	}
	if (start == -1 || end == -1)
		project_free(ERR_LINKS);
	if (!matrix[start][end] && !matrix[end][start])
	{
		matrix[start][end] = TRUE;
		matrix[end][start] = TRUE;
	}
	else
		project_free(ERR_LINK_DUPLICATE);
}

_Bool			get_link(char *str)
{
	_Bool	is_link;
	char	**table;

	is_link = FALSE;
	if (!(table = ft_strsplit(str, '-')))
		project_free(ERR_ROOM_PARSING);
	if (row_count(table) == 2)
	{
		mark_matrix(table, g_lem_in->matrix, g_lem_in->names);
		is_link = TRUE;
	}
	free_words(&table);
	return (is_link);
}

_Bool			get_command(char *str)
{
	if (str)
	{
		if (!ft_strcmp(str, "##start"))
		{
			if (g_lem_in->start == -1)
				g_lem_in->start = g_lem_in->rooms + 1;
			else
				project_free(ERR_START_ROOM);
			return (TRUE);
		}
		if (!ft_strcmp(str, "##end"))
		{
			if (g_lem_in->end == -1)
				g_lem_in->end = g_lem_in->rooms + 1;
			else
				project_free(ERR_END_ROOM);
			return (TRUE);
		}
	}
	return (FALSE);
}

_Bool			get_room(char *str)
{
	_Bool	is_room;
	char	**table;

	is_room = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		project_free(ERR_ROOM_PARSING);
	if (row_count(table) == 3)
	{
		add_room(table, &g_lem_in->nodes);
		rooms_duplicate(g_lem_in->nodes);
		is_room = TRUE;
		g_lem_in->rooms++;
	}
	if (!is_room)
		free_words(&table);
	return (is_room);
}
