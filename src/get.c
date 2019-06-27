#include "lem_in.h"

_Bool		get_command(t_lem_in *lem_in, char *str)
{
	if (str)
	{
		if (!ft_strcmp(str, "##start"))
		{
			if (!lem_in->start)
				lem_in->start = lem_in->rooms + 1;
			else
				print_error(ERR_START_ROOM);
			return (TRUE);
		}
		if (!ft_strcmp(str, "##end"))
		{
			if (!lem_in->end)
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
	_Bool	result;
	char	**table;

	result = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		print_error(ERR_ROOM_PARSING);
	if (row_count(table) == 3)
	{
		add_room(table, &lem_in->nodes);
		rooms_duplicate(lem_in->nodes);
		result = TRUE;
		lem_in->rooms++;
	}
	if (!result)
		free_words(&table);
	return (result);
}

void		mark_matrix(t_links *links, _Bool **matrix, char **names)
{
	int	i;
	int	end;
	int	start;
	
	i = 0;
	end = -1;
	start = -1;
	while ((start == -1 || end == -1) && names[i])
	{
		if (!ft_strcmp(links->a, names[i]))
			start = i;
		if (!ft_strcmp(links->b, names[i]))
			end = i;
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
	_Bool	result;
	char	**table;

	result = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		print_error(ERR_ROOM_PARSING);
	if (row_count(table) == 2)
	{
		add_link(table, &lem_in->links);
		mark_matrix(lem_in->links, lem_in->matrix, lem_in->names);
		result = TRUE;
	}
	if (!result)
		free_words(&table);
	return (result);
}
