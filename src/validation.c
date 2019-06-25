#include "lem_in.h"

static char	*read_rooms(t_valid *map, char *line, int stat)
{
	while (stat != -2)
	{
		if ((stat == 2 || stat == 3) && get_next_line(0, &line) && ++map->num_r)
		{
			if (check_comment(line) != -1 || (stat == 2 && map->start) ||
				(stat == 3 && map->end) || room_exist(line, map->rooms, 1))
				error(0);
			map->start = stat == 2 ? line : map->start;
			map->end = stat == 3 ? line : map->end;
			push_elem(line, &map->data);
			add_elem(line, &map->rooms);
		}
		else if (stat == -1 && ++map->num_r)
		{
			if (room_exist(line, map->rooms, 1))
				error(0);
			add_elem(line, &map->rooms);
		}
		if (!get_next_line(0, &line) || !(stat = check_comment(line)))
			error();
		push_elem(line, &map->data);
	}
	if (!map->start || !map->end)
		error();
	return (line);
}

static void	read_links(t_valid *map, char *line)
{
	int		stat;

	stat = -2;
	while (stat)
	{
		if (stat == -2)
		{
			if (link_n_ok(line, map->rooms, map->links))
				error();
			else
				add_elem(line, &map->links);
		}
		if (!get_next_line(0, &line))
			break ;
		if (!(stat = check_comment(line)) || stat == -1)
			error();
		push_elem(line, &map->data);
	}
	return ;
}

int			read_data(t_valid *map)
{
	char	*line;
	int		stat;

	stat = 0;
	line = 0;
	line = read_rooms(map, line, stat);
	read_links(map, line);
	return (1);
}
