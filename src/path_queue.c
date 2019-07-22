/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:43:19 by gdamion-          #+#    #+#             */
/*   Updated: 2019/07/21 14:02:56 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

_Bool		if_q_empty(t_room *q, int id)
{
	while (q)
	{
		if (q->id == id)
			return (FALSE);
		q = q->next;
	}
	return (TRUE);
}

void		q_push(t_room *q, int new_id, int prev_id, _Bool enter)
{
	while (q->next)
		q = q->next;
	q->next = init_queue(new_id, prev_id, q, enter);
}

_Bool		queue_pop(t_room **q)
{
	t_room	*next_el;
	t_room	*prev_el;

	if (q && *q)
	{
		next_el = (*q)->next;
		prev_el = (*q)->prev;
		prev_el->next = next_el;
		next_el->prev = prev_el;
		free(*q);
		*q = prev_el;
		return (TRUE);
	}
	else
		return (FALSE);
}

t_room		*init_queue(int new_id, int prev_id, t_room *prev, _Bool enter)
{
	t_room	*q;
	t_room	*buf;

	if (!(q = (t_room*)malloc(sizeof(t_room))))
	{
		while (prev)
		{
			buf = prev;
			prev = prev->prev;
			free(buf);
		}
		project_free(ERR_ALLOC, 0);
	}
	q->next = NULL;
	q->id = new_id;
	q->entr = enter;
	q->prev = prev;
	q->from = prev_id;
	return (q);
}
