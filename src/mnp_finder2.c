#include "lem_in.h"

_Bool		**np_init(void)
{
	_Bool	**n;
	int		a;

	a = 0;
	if (!(n = (_Bool**)malloc(sizeof(_Bool*) * g_info->n_rooms)))
		error();
	while (a < g_info->n_rooms)
	{
		if (!(n[a] = (_Bool*)malloc(sizeof(_Bool) * (g_info->n_rooms))))
		{
			while (--a >= 0)
				free(n[a]);
			error();
		}
		ft_bzero(n[a], sizeof(char) * g_info->n_rooms);
		a++;
	}
	return (n);
}

void		np_cpy(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_info->n_rooms)
	{
		j = 0;
		while (j < g_info->n_rooms)
		{
			g_mnp[i][j] = g_np[i][j];
			j++;
		}
		i++;
	}
}

void		set_path(t_room *path)
{
	t_room	*buf;

	buf = path;
	path = path->next;
	free(buf);
	while (path)
	{
		g_np[path->from][path->id] = TRUE;
		buf = path;
		path = path->next;
		free(buf);
	}
}

void		get_residual_network(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_info->n_rooms)
	{
		j = 0;
		while (j < g_info->n_rooms)
		{
			if (g_info->links[i][j] && (int)g_np[i][j])
				g_info->links[i][j] = FALSE;
			j++;
		}
		i++;
	}
}

int			find_np(void)
{
	t_room	*path;

	path = find_path(0, 0);
	if (!path)
		return (0);
	set_path(path);
	return (1);
}
