#include "lem_in.h"

void			parse_ants(t_lem_in *lem_in, char **buffer)
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
				if ((lem_in->ants = ft_atoi(*buffer)) < 1)
					terminate(ERR_NUM_ANTS);	
			}
			else if (is_room(*buffer) || is_command(*buffer))
				return ;
			else
				terminate(ERR_READING);
		}
		push_elem(*buffer, &lem_in->data);
	}
}

void			parse_rooms(t_lem_in *lem_in, char **buffer)
{
	size_t		size;
	int			rooms;

	rooms = 0;
	while (*buffer || (size = get_next_line(0, buffer)))
	{
		if (size == -1)
			terminate(ERR_READING);
		if (!get_room(lem_in, *buffer))
			if (!get_command(lem_in, *buffer))
				if (!is_comment(*buffer))
					if (is_link(*buffer))
					{
						return ;
					}
					else
						terminate(ERR_ROOM_PARSING);
		*buffer = 0;
		push_elem(*buffer, &lem_in->data);
	}
	return ;
}

void			parse_links(t_lem_in *lem_in, char **buffer)
{
	size_t		size;
	char		line;
	int			rooms;

	rooms = 0;
	while (*buffer || (size = get_next_line(0, &line)))
	{
		if (size == -1)
			terminate(ERR_READING);
		if (!get_link(lem_in, *buffer))
			if (!is_comment(*buffer))
				terminate(ERR_ROOM_PARSING);
		*buffer = 0;
		push_elem(line, &lem_in->data);
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

int			is_integer(char *s)
{
	char	*new;
	int		result;
	int		integer;

	integer = ft_atoi(s);
	new = ft_itoa(integer);
	if (!(result = ft_strcmp(new, s)))
		terminate(ERR_READING);
	free(new);
	return (!result ? integer : -1);
}

void			check_duplicate(t_lem_in *lem_in, )
{
	
}

char			**set_names(t_lem_in *lem_in)
{
	int			i;
	char		**names;
	
	i = 0;
	names = ft_wordsnew(lem_in->rooms);
	while (i < lem_in->rooms)
		names[i++] = lem_in->nodes->line;
	swap_names(names, 0, lem_in->start);
	swap_names(names, lem_in->rooms - 1, lem_in->end);
}

t_lem_in		*get_antshill(void)
{
	char		*buffer;
	t_lem_in	*lem_in;

	buffer = 0;
	if (INIT_LEM_IN)
		terminate(ERR_LEM_IN_INIT);
	parse_ants(lem_in, &buffer);
	parse_rooms(lem_in, &buffer);
	lem_in->names = set_names(lem_in);
	lem_in->matrix = init_matrix(lem_in->rooms);
	if (!lem_in->start || !lem_in->end)
		terminate(ERR_START_END_ROOM);
	parse_links(lem_in, &buffer);
}