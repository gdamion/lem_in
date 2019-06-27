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
				lem_in->ants = ft_atoi(*buffer);
			else
				return ;
		}
		add_elem(*buffer, &lem_in->data);
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
		if (!get_command(lem_in, *buffer))
		{
			if (!is_comment(*buffer))
			{
				if (!get_room(lem_in, *buffer))
				{
					if (is_link(*buffer))
						return ;
					else
						print_error(ERR_ROOM_PARSING);
				}
			}
		}
		*buffer = 0;
		add_elem(*buffer, &lem_in->data);
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
		if (!is_comment(*buffer))
			if (!get_link(lem_in, *buffer))
				print_error(ERR_ROOM_PARSING);
		*buffer = 0;
		add_elem(*buffer, &lem_in->data);
	}
	return ;
}

t_lem_in		*anthill(void)
{
	char		*buffer;
	t_lem_in	*lem_in;

	buffer = 0;
	if (INIT_LEM_IN)
		print_error(ERR_LEM_IN_INIT);
	ft_bzero(lem_in, sizeof(t_lem_in));
	lem_in->start = -1;
	lem_in->end = -1;
	parse_ants(lem_in, &buffer);
	if (lem_in->ants < 1)
		print_error(ERR_NUM_ANTS);
	parse_rooms(lem_in, &buffer);
	if (lem_in->start == -1 || lem_in->end == -1)
		print_error(ERR_START_END_ROOM);
	lem_in->names = set_names(lem_in, lem_in->nodes);
	lem_in->matrix = init_matrix(lem_in->rooms);
	parse_links(lem_in, &buffer);
	if (!lem_in->links_a || !lem_in->links_b)
		print_error(ERR_NO_LINKS);
	return (lem_in);
}