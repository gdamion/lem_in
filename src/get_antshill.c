#include "lem_in.h"

void			parse_ants(t_valid *data, char **buffer)
{
	size_t		size;

	while ((size = get_next_line(0, &buffer)))
	{
		if (size == -1)
			terminate(ERR_READING);
		if (!is_comment(*buffer))
		{
			if (is_int(*buffer, TRUE))
			{
				if ((data->ants = ft_atoi(*buffer)) < 1)
					terminate(ERR_NUM_ANTS);	
			}
			else if (is_room(*buffer) || is_command(*buffer))
				return ;
			else
				terminate(ERR_READING);
		}
		push_elem(*buffer, &data->data);
	}
}

void			parse_rooms(t_valid *data, char **buffer)
{
	size_t		size;
	int			rooms;

	rooms = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			terminate(ERR_READING);
		if (!get_room(data, *buffer))
			if (!get_command(data, *buffer))
				if (!is_comment(*buffer))
					if (is_link(*buffer))
					{
						return ;
					}
					else
						terminate(ERR_ROOM_PARSING);
		*buffer = 0;
		push_elem(*buffer, &data->data);
	}
	return ;
}

void			parse_links(t_valid *data, char **buffer)
{
	size_t		size;
	char		line;
	int			rooms;

	rooms = 0;
	while (*buffer || (size = get_next_line(0, &line)))
	{
		if (size == -1)
			terminate(ERR_READING);
		if (!get_link(data, *buffer))
			if (!is_comment(*buffer))
				terminate(ERR_ROOM_PARSING);
		*buffer = 0;
		push_elem(line, &data->data);
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

void			check_duplicate(t_valid *data, )
{
	
}

char			**set_names(t_valid *data)
{
	int			i;
	char		**names;
	
	i = 0;
	names = ft_wordsnew(data->rooms);
	while (i < data->rooms)
		names[i++] = data->nodes->line;
	swap_names(names, 0, data->start);
	swap_names(names, data->rooms - 1, data->end);
}

t_lem_in		*get_antshill(void)
{
	char		*buffer;
	t_lem_in	*lem_in;
	t_valid		*data;

	buffer = 0;
	if (INIT_LEM_IN)
		terminate(ERR_LEM_IN_INIT);
	parse_ants(data, &buffer);
	parse_rooms(data, &buffer);
	lem_in->names = set_names(data);
	lem_in->matrix = init_matrix(lem_in->rooms);
	if (!lem_in->start || !lem_in->end)
		terminate(ERR_START_END_ROOM);
	parse_links(lem_in, &buffer);
}