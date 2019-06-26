#include "lem_in.h"

static char	*read_nodes(t_valid *map, char *line, int lvl)
{
	while (lvl != -2)
	{
		if ((lvl == 2 || lvl == 3) && get_next_line(0, &line) && ++map->num_r)
		{
			if (check_comment(line) != -1 || (lvl == 2 && map->start) ||
				(lvl == 3 && map->end) || room_exist(line, map->rooms, 1))
				print_error(0);
			map->start = lvl == 2 ? line : map->start;
			map->end = lvl == 3 ? line : map->end;
			push_elem(line, &map->data);
			add_elem(line, &map->rooms);
		}
		else if (lvl == -1 && ++map->num_r)
		{
			if (room_exist(line, map->rooms, 1))
				print_error(0);
			add_elem(line, &map->rooms);
		}
		if (!get_next_line(0, &line) || !(lvl = check_comment(line)))
			print_error();
		push_elem(line, &map->data);
	}
	if (!map->start || !map->end)
		print_error();
	return (line);
}

static void	read_links(t_valid *map, char *line)
{
	int		lvl;

	lvl = -2;
	while (lvl)
	{
		if (lvl == -2)
		{
			if (link_ok(line, map->rooms, map->links))
				print_error();
			else
				add_elem(line, &map->links);
		}
		if (!get_next_line(0, &line))
			break ;
		if (!(lvl = check_comment(line)) || lvl == -1)
			print_error();
		push_elem(line, &map->data);
	}
	return ;
}

int			read_data(t_valid *map)
{
	char	*line;
	int		lvl;

	lvl = 0;
	line = 0;
	line = read_nodes(map, line, lvl);
	read_links(map, line);
	return (1);
}
