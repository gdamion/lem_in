#include "lem_in.h"

_Bool		**init_matrix(int rooms)
{
	int		a;
	_Bool	**matrix;

	a = 0;
	if (!(matrix = (_Bool**)malloc(sizeof(_Bool*) * rooms)))
		print_error(ERR_LINE_INIT);
	while (a < rooms)
	{
		if (!(matrix[a] = (_Bool*)malloc(sizeof(_Bool) * rooms)))
		{
			while (--a >= 0)
				free(matrix[a]);
			print_error(ERR_MATRIX_INIT);
		}
		ft_bzero(matrix[a], sizeof(char) * rooms);
		a++;
	}
	return (matrix);
}

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
			if (g_lem_in->links[i][j] && (int)g_np[i][j])
				g_lem_in->links[i][j] = FALSE;
			j++;
		}
		i++;
	}
}

int			find_ways(void)
{
	t_room	*path;

	path = find_path(0, 0);
	if (!path)
		return (0);
	set_path(path);
	return (1);
}
