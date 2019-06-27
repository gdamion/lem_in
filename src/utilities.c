#include "lem_in.h"

void			swap_names(char **names, int a, int b)
{
	char		*temp;

	temp = names[a];
	names[a] = names[b];
	names[b] = temp;
}

void			rooms_duplicate(t_rooms *nodes)
{
	t_rooms		*temp;

	temp = nodes->next;
	while (temp)
	{
		if (!ft_strcmp(nodes->name, temp->name))
			print_error(ERR_ROOM_DUPLICATE);
		if (nodes->x == temp->x && nodes->y == temp->y)
			print_error(ERR_ROOM_DUPLICATE);
		temp = temp->next;
	}
}

void			links_duplicate(t_links *links)
{
	t_links		*temp;

	temp = links->next;
	while (temp)
	{
		if ((!ft_strcmp(links->a, temp->a) && !ft_strcmp(links->b, temp->b)) ||
			(!ft_strcmp(links->a, temp->b) && !ft_strcmp(links->b, temp->a)))
			print_error(ERR_LINK_DUPLICATE);
		temp = temp->next;
	}
}

char			**set_names(t_lem_in *lem_in, t_rooms *nodes)
{
	int			i;
	char		**names;
	
	i = lem_in->rooms - 1;
	(void)nodes;
	names = ft_wordsnew(lem_in->rooms);
	while (i >= 0)
	{
		names[i] = nodes->name;
		nodes = nodes->next;
		i--;
	}
	swap_names(names, 0, lem_in->start - 1);
	swap_names(names, lem_in->rooms - 1, lem_in->end - 1);
	return (names);
}

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
