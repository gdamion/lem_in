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
				terminate(ERR_START_ROOM);
			return (TRUE);
		}
		if (!ft_strcmp(str, "##end"))
		{
			if (!lem_in->end)
				lem_in->end = lem_in->rooms + 1;
			else
				terminate(ERR_END_ROOM);
			return (TRUE);
		}
	}
	return (FALSE);
}

_Bool		get_room(t_lem_in *lem_in, char *str)
{
	char	**table;
	_Bool	result;

	result = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		terminate(ERR_ROOM_PARSING);
	if (row_count(table) == 3)
	{
		if (valid_name(table[0])
			&& is_int(table[1], TRUE)
			&& is_int(table[2], TRUE))
		{
			push_elem(table, &lem_in->nodes);
			check_duplicate(lem_in->nodes);
			result = TRUE;
			lem_in->rooms++;
		}
	}
	if (!result)
		free_words(&table);
	return (result);
}

_Bool		get_link(t_lem_in *lem_in, char *str)
{
	char	**table;
	_Bool	result;

	result = FALSE;
	if (!(table = ft_strsplit(str, ' ')))
		terminate(ERR_ROOM_PARSING);
	if (row_count(table) == 2)
	{
		push_elem(table, &lem_in->links);
		result = TRUE;
		lem_in->lnks++;
	}
	if (!result)
		free_words(&table);
	return (result);
}
