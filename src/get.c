#include "lem_in.h"

static void		mark_matrix(t_lem_in *lem_in, _Bool **matrix, char **names)
{
	int	i;
	int	end;
	int	start;
	
	i = 0;
	end = -1;
	start = -1;
	while ((start == -1 || end == -1) && names[i])
	{
		if (!ft_strcmp(lem_in->links_a, names[i]))
			start = i;
		if (!ft_strcmp(lem_in->links_b, names[i]))
			end = i;
		i++;
	}
	if (start == -1 || end == -1)
		print_error(ERR_LINKS);
	if (!matrix[start][end] && !matrix[end][start])
	{
		matrix[start][end] = TRUE;
		matrix[end][start] = TRUE;
	}
	else
		print_error(ERR_LINK_DUPLICATE);
}

_Bool		get_link(t_lem_in *lem_in, char *str)
{
	_Bool	is_link;
	char	**table;

	is_link = FALSE;
	if (!(table = ft_strsplit(str, '-')))
		print_error(ERR_ROOM_PARSING);
	if (row_count(table) == 2)
	{
		lem_in->links_a = table[0];
		lem_in->links_b = table[1];
		mark_matrix(lem_in, lem_in->matrix, lem_in->names);
		is_link = TRUE;
	}
	if (!is_link)
		free_words(&table);
	return (is_link);
}

_Bool		get_command(t_lem_in *lem_in, char *str)
{
	if (str)
	{
		if (!ft_strcmp(str, "##start"))
		{
			if (lem_in->start == -1)
				lem_in->start = lem_in->rooms + 1;
			else
				print_error(ERR_START_ROOM);
			return (TRUE);
		}
		if (!ft_strcmp(str, "##end"))
		{
			if (lem_in->end == -1)
				lem_in->end = lem_in->rooms + 1;
			else
				print_error(ERR_END_ROOM);
			return (TRUE);
		}
	}
	return (FALSE);
}

_Bool		get_room(t_lem_in *lem_in, char *str)
{
	_Bool	is_room;
	char	**table;

	is_room = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		print_error(ERR_ROOM_PARSING);
	if (row_count(table) == 3)
	{
		add_room(table, &lem_in->nodes);
		rooms_duplicate(lem_in->nodes);
		is_room = TRUE;
		lem_in->rooms++;
	}
	if (!is_room)
		free_words(&table);
	return (is_room);
}
