/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:42:47 by gdamion-          #+#    #+#             */
/*   Updated: 2019/07/21 14:44:56 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		parse_ants(char **buffer)
{
	int			size;

	while ((size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!is_comment(*buffer))
		{
			if (is_int(*buffer, TRUE))
				g_lem_in->ants = ft_atoi(*buffer);
			else
				return ;
		}
		add_elem(buffer, &g_lem_in->data);
	}
}

static void		parse_rooms(char **buffer)
{
	int			size;

	size = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!get_command(*buffer))
		{
			if (!is_comment(*buffer))
			{
				if (!get_room(*buffer))
				{
					if (is_link(*buffer))
						return ;
					else
						project_free(ERR_ROOM_PARSING);
				}
			}
		}
		add_elem(buffer, &g_lem_in->data);
		*buffer = 0;
	}
	return ;
}

static void		parse_links(char **buffer)
{
	int			size;

	size = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!is_comment(*buffer))
			if (!get_link(*buffer))
				project_free(ERR_ROOM_PARSING);
		add_elem(buffer, &g_lem_in->data);
		*buffer = 0;
	}
	return ;
}

t_lem_in		*get_anthill(void)
{
	char		*buffer;

	buffer = 0;
	init_lem();
	parse_ants(&buffer);
	if (g_lem_in->ants < 1)
		project_free(ERR_NUM_ANTS);
	parse_rooms(&buffer);
	if (g_lem_in->start == -1 || g_lem_in->end == -1)
		project_free(ERR_START_END_ROOM);
	g_lem_in->names = set_names(&g_lem_in->nodes);
	g_lem_in->status = ft_strnew(g_lem_in->rooms);
	g_lem_in->matrix = init_matrix(g_lem_in->rooms);
	parse_links(&buffer);
	return (g_lem_in);
}
