#include "lem_in.h"

void		add_elem(char *line, t_lst **lst)
{
	t_lst	*new;

	new = ft_memalloc(sizeof(t_lst));
	new->next = *lst;
	new->line = line;
	*lst = new;
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
	return (integer);
}

void		add_rooms(char **table, t_rooms **rooms)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	new->name = valid_name(table[0]);
	new->x = is_integer(table[1]);
	new->y = is_integer(table[2]);
	new->next = *rooms;
	*rooms = new;
}

void		push_elem(char *line, t_lst **lst)
{
	t_lst	*p;
	t_lst	*new;

	p = *lst;
	if (!p)
	{
		*lst = ft_memalloc(sizeof(t_lst));
		(*lst)->next = NULL;
		(*lst)->line = line;
	}
	else
	{
		while (p->next)
			p = p->next;
		new = ft_memalloc(sizeof(t_lst));
		new->next = NULL;
		new->line = line;
		p->next = new;
	}
}
