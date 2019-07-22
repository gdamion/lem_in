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

static void		get_position(char **table, int *start, int *end)
{
	int	i;

	i = 0;
	while ((*start == -1 || *end == -1) && g_lem_in->names[i])
	{
		if (!ft_strcmp(table[0], g_lem_in->names[i]))
			*start = i;
		if (!ft_strcmp(table[1], g_lem_in->names[i]))
			*end = i;
		i++;
	}
	if (*start == -1 || *end == -1)
	{
		free_words(&table);
		project_free(ERR_LINKS);
	}
}

static void		mark_matrix(char **table)
{
	int	start;
	int	end;
	
	end = -1;
	start = -1;
	get_position(table, &start, &end);
	if (!g_lem_in->matrix[start][end] && !g_lem_in->matrix[end][start])
	{
		g_lem_in->matrix[start][end] = TRUE;
		g_lem_in->matrix[end][start] = TRUE;
	}
	else
	{
		free_words(&table);
		project_free(ERR_LINK_DUPLICATE);
	}
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
		mark_matrix(table);
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
