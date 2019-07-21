/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:43:00 by gdamion-          #+#    #+#             */
/*   Updated: 2019/07/19 16:20:47 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*record_path(t_room *q)
{
	int			buf_id;

	while (q->next)
		q = q->next;
	buf_id = q->from;
	q = q->prev;
	while (q->id)
	{
		if (q->id == buf_id && q->id &&
			q->id != (g_lem_in->rooms - 1))
		{
			g_lem_in->status[q->id] = TRUE;
			buf_id = q->from;
			q = q->prev;
		}
		else
			queue_pop(&q);
	}
	return (q);
}

static _Bool	cross(int prev, int for_check)
{
	int			s;

	s = 0;
	while (s < g_lem_in->rooms)
	{
		if (s && s != prev && g_lem_in->matrix[for_check][s]
							&& g_lem_in->status[s])
			return (TRUE);
		s++;
	}
	return (FALSE);
}

static void		clean_queue(t_room *q)
{
	t_room		*buf;

	while (q)
	{
		buf = q;
		q = q->next;
		free(buf);
	}
}

t_room			*find_path(int i, int j)
{
	t_room		*q;
	t_room		*q_st;

	q = init_queue(0, -1, NULL, 0);
	q_st = q;
	while (q)
	{
		i = q->id;
		j = 0;
		while (++j < g_lem_in->rooms)
			if (g_lem_in->matrix[i][j] && i != j && if_q_empty(q_st->next, j))
			{
				if ((!STATUS(j) && !q->entr) || (STATUS(i) && STATUS(j)))
					q_push(q, j, i, 0);
				else if (STATUS(j))
					cross(i, j) ? q_push(q, j, i, 1) : 1;
			}
		if (g_lem_in->matrix[i][--j])
			return (record_path(q));
		q = q->next;
	}
	clean_queue(q_st);
	return (NULL);
}
