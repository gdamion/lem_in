#include "lem_in.h"

t_room		*record_path(t_room *q)
{
	int		buf_id;

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

_Bool		cross(int prev, int for_check)
{
	int		s;

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

void		clean_queue(t_room *q)
{
	t_room	*buf;

	while (q)
	{
		buf = q;
		q = q->next;
		free(buf);
	}
}

t_room		*find_path(int i, int j)
{
	t_room	*q;
	t_room	*q_st;

	q = init_queue(0, -1, NULL);
	q_st = q;
	while (q)
	{
		i = q->id;
		j = 0;
		while (++j < g_lem_in->rooms)
			if (g_lem_in->matrix[i][j] && i != j && if_q_empty(q_st->next, j))
			{
				if (STATUS(j) == 0 || (STATUS(i) == 1 && STATUS(j) == 1))
					q_push(q, j, i);
				else if (STATUS(j) == 1)
					cross(i, j) ? (q_push(q, j, i)) : 1;
			}
		if (g_lem_in->matrix[i][--j])
			return (record_path(q));
		q = q->next;
	}
	clean_queue(q_st);
	return (NULL);
}
