#include "lem_in.h"

void		cpy_ways(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_lem_in->rooms)
	{
		j = 0;
		while (j < g_lem_in->rooms)
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
	while (i < g_lem_in->rooms)
	{
		j = 0;
		while (j < g_lem_in->rooms)
		{
			if (g_lem_in->matrix[i][j] && (int)g_np[i][j])
				g_lem_in->matrix[i][j] = FALSE;
			j++;
		}
		i++;
	}
}

int			find_paths(void)
{
	t_room	*path;

	path = find_path(0, 0);
	if (!path)
		return (0);
	set_path(path);
	return (1);
}
