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
		if (q->id == buf_id && q->id && q->id != (g_info->n_rooms - 1))
		{
			g_info->nodes[q->id]->status = TRUE;
			buf_id = q->from;
			q = q->prev;
		}
		else
			q_pop(&q);
	}
	return (q);
}

_Bool		check_suurb_friends(int prev, int for_check)
{
	int		s;

	s = 0;
	while (s < g_info->n_rooms)
	{
		if (s && s != prev && g_info->links[for_check][s] \
							&& g_info->nodes[s]->status)
			return (TRUE);
		s++;
	}
	return (FALSE);
}

void		q_clean(t_room *q)
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
	t_room	*q_start;

	q = q_create(0, -1, NULL);
	q_start = q;
	while (q)
	{
		i = q->id;
		j = 0;
		while (++j < g_info->n_rooms)
			if (g_info->links[i][j] && i != j && if_q_empty(q_start->next, j))
			{
				if (g_info->nodes[j]->status == 0 || (g_info->nodes[i]->status \
									== 1 && g_info->nodes[j]->status == 1))
					q_push(q, j, i);
				else if (g_info->nodes[j]->status == 1)
					check_suurb_friends(i, j) ? (q_push(q, j, i)) : 1;
			}
		if (g_info->links[i][--j])
			return (record_path(q));
		q = q->next;
	}
	q_clean(q_start);
	return (NULL);
}
