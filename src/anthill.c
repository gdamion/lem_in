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

void			parse_ants(t_lem_in *lem_in, char **buffer)
{
	int			size;

	while ((size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!is_comment(*buffer))
		{
			if (is_int(*buffer, TRUE))
				lem_in->ants = ft_atoi(*buffer);
			else
				return ;
		}
		add_elem(buffer, &lem_in->data);
		*buffer = 0;
	}
}

void			parse_rooms(t_lem_in *lem_in, char **buffer)
{
	int			size;

	size = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!get_command(lem_in, *buffer))
		{
			if (!is_comment(*buffer))
			{
				if (!get_room(lem_in, *buffer))
				{
					if (is_link(*buffer))
						return ;
					else
						project_free(ERR_ROOM_PARSING);
				}
			}
		}
		add_elem(buffer, &lem_in->data);
		*buffer = 0;
	}
	return ;
}

void			parse_links(t_lem_in *lem_in, char **buffer)
{
	int			size;

	size = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			project_free(ERR_READING);
		if (!is_comment(*buffer))
			if (!get_link(lem_in, *buffer))
				project_free(ERR_ROOM_PARSING);
		add_elem(buffer, &lem_in->data);
		*buffer = 0;
	}
	return ;
}

t_lem_in		*get_anthill(void)
{
	char		*buffer;

	buffer = 0;
	init_lem();
	parse_ants(g_lem_in, &buffer);
	if (g_lem_in->ants < 1)
		project_free(ERR_NUM_ANTS);
	parse_rooms(g_lem_in, &buffer);
	if (g_lem_in->start == -1 || g_lem_in->end == -1)
		project_free(ERR_START_END_ROOM);
	g_lem_in->names = set_names(g_lem_in, &g_lem_in->nodes);
	g_lem_in->status = ft_strnew(g_lem_in->rooms);
	g_lem_in->matrix = init_matrix(g_lem_in->rooms);
	parse_links(g_lem_in, &buffer);
	return (g_lem_in);
}
