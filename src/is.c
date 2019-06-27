#include "lem_in.h"

_Bool				is_comment(char *str)
{
	if (str)
	{
		if (ft_strlen(str)
			&& !is_command(str)
			&& !ft_strncmp(str, "#", 1))
			return (TRUE);
	}
	return (FALSE);
}

_Bool				is_link(char *str)
{
	char			**table;

	if (!(table = ft_strsplit(str, '-')))
		print_error(ERR_ROOM_PARSING);
	if (row_count(table) == 2)
	{
		free_words(&table);
		return (TRUE);
	}
	else
	{
		free_words(&table);
		return (FALSE);
	}
}

_Bool				is_command(char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 2
			&& !ft_strncmp(str, "##", 2))
			return (TRUE);
	}
	return (FALSE);
}

int					is_integer(char *s)
{
	char			*new;
	int				result;
	int				integer;

	integer = ft_atoi(s);
	new = ft_itoa(integer);
	if (!(result = ft_strcmp(new, s)))
		print_error(ERR_READING);
	free(new);
	return (integer);
}


_Bool				is_int(const char *str, _Bool strict)
{
	unsigned int	result;
	unsigned int	border;
	int				i;
	int				sign;
	int				digits;

	result = 0;
	digits = 0;
	border = (unsigned int)(MAX_INT / 10);
	i = 0;
	while (!strict && SP(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && ++digits)
	{
		if (((result > border || (result == border && (str[i] - '0') > 7))
				&& sign == 1)
			|| ((result > border || (result == border && (str[i] - '0') > 8))
				&& sign == -1))
			return (FALSE);
		result = result * 10 + (str[i++] - '0');
	}
	return (!str[i] && digits);
}

size_t		row_count(char **table)
{
	size_t	size;

	size = 0;
	if (table)
		while (*table)
		{
			size++;
			table++;
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
