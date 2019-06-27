#include "lem_in.h"

size_t		row_count(char **table)
{
	size_t	size;

	size = 0;
	if (table)
	{
		while (*table)
		{
			size++;
			table++;
		}
	}
	return (size);
}

_Bool	valid_name(char *str)
{
	if (str && ft_strlen(str))
	{
		if (str[0] != 'L' && str[0] != '#')
			return (TRUE);
	}
	return (FALSE);
}
