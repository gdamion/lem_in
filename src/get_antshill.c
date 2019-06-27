#include "lem_in.h"

void			parse_ants(t_lem_in *lem_in, char **buffer)
{
	int			size;

	while ((size = get_next_line(0, buffer)))
	{
		if (size == -1)
			print_error(ERR_READING);
		if (!is_comment(*buffer))
		{
			if (is_int(*buffer, TRUE))
			{
				if ((lem_in->ants = ft_atoi(*buffer)) < 1)
					print_error(ERR_NUM_ANTS);	
			}
			else
				return ;
		}
		push_elem(*buffer, &lem_in->data);
	}
}

void			parse_rooms(t_lem_in *lem_in, char **buffer)
{
	int			size;

	size = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			print_error(ERR_READING);
		if (!get_room(lem_in, *buffer))
		{
			if (!get_command(lem_in, *buffer))
			{
				if (!is_comment(*buffer))
				{
					if (is_link(*buffer))
						return ;
					else
						print_error(ERR_ROOM_PARSING);
				}
			}
		}	
		*buffer = 0;
		push_elem(*buffer, &lem_in->data);
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
			print_error(ERR_READING);
		if (!get_link(lem_in, *buffer))
			if (!is_comment(*buffer))
				print_error(ERR_ROOM_PARSING);
		*buffer = 0;
		push_elem(*buffer, &lem_in->data);
		return ;
	}
}

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

char			**set_names(t_lem_in *lem_in, t_rooms *nodes)
{
	int			i;
	char		**names;
	
	i = 0;
	names = ft_wordsnew(lem_in->rooms);
	while (i < lem_in->rooms)
	{
		names[i] = nodes->name;
		nodes = nodes->next;
		i++;
	}
	swap_names(names, 0, lem_in->start);
	swap_names(names, lem_in->rooms - 1, lem_in->end);
	return (names);
}

t_lem_in		*get_antshill(void)
{
	char		*buffer;
	t_lem_in	*lem_in;

	buffer = 0;
	if (INIT_LEM_IN)
		print_error(ERR_LEM_IN_INIT);
	parse_ants(lem_in, &buffer);
	ft_printf("------ %d ------\n", lem_in->ants);
	parse_rooms(lem_in, &buffer);
	lem_in->names = set_names(lem_in, lem_in->nodes);
	lem_in->matrix = init_matrix(lem_in->rooms);
	if (!lem_in->start || !lem_in->end)
		print_error(ERR_START_END_ROOM);
	parse_links(lem_in, &buffer);
	if (!lem_in->links)
		print_error(ERR_NO_LINKS);
	return (lem_in);
}