#include "lem_in.h"

int			count_ways(void)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (i < g_lem_in->rooms)
	{
		if (g_mnp[0][i])
			cnt++;
		i++;
	}
	return (cnt);
}

int			path_len(int i, t_id *l_id)
{
	int len;
	int j;

	len = 1;
	j = 0;
	while (i + 1)
		g_mnp[0][j++] ? (i--) : 1;
	i = --j;
	l_id->id = i;
	while (i < (g_lem_in->rooms - 1))
	{
		j = 0;
		while (!g_mnp[i][j])
			j++;
		if (!((*l_id).next = (t_id*)malloc(sizeof(t_id))))
			return (-1);
		l_id = l_id->next;
		l_id->id = j;
		len++;
		i = j;
	}
	l_id->next = NULL;
	return (len);
}

void		free_in_alloc(t_pathkit *p_kit, t_id **l_id, int *i)
{
	t_id *buf;

	while (*l_id)
	{
		buf = *l_id;
		*l_id = (*l_id)->next;
		free(buf);
	}
	while (--(*i) >= 0)
		free(p_kit->paths[*i].room);
	free(p_kit->paths);
	termination();
}

void		fill(t_pathkit *p_kit, t_id **l_id, int *i)
{
	if (!(*l_id = (t_id*)malloc(sizeof(t_id))))
		free_in_alloc(p_kit, l_id, i);
	p_kit->paths[*i].ants = 0;
	p_kit->paths[*i].index = 0;
	(p_kit->paths[*i].len = path_len(*i, *l_id)) == -1 ? \
							free_in_alloc(p_kit, l_id, i) : 1;
	if (!(p_kit->paths[*i].room = \
			(int*)malloc(sizeof(int) * p_kit->paths[*i].len)))
		free_in_alloc(p_kit, l_id, i);
}

t_pathkit		set_paths_kit(void)
{
	t_pathkit	p_kit;
	t_id		*l_id;
	t_id		*buf;
	int			i;
	int			j;

	i = -1;
	l_id = NULL;
	(!(p_kit.len = count_ways())) ? termination() : 1;
	!(p_kit.paths = PATHS()) ? termination() : 1;
	while (++i < p_kit.len)
	{
		fill(&p_kit, &l_id, &i);
		j = 0;
		buf = l_id;
		while (j < p_kit.paths[i].len)
		{
			p_kit.paths[i].room[j++] = l_id->id;
			l_id = l_id->next;
			free(buf);
			buf = l_id;
		}
	}
	free(l_id);
	return (p_kit);
}
