#include "lem_in.h"

void	free_t_valid(t_valid *me)
{
	free_lst(me->rooms, 0);
	free_lst(me->links, 0);
	free(me->names);
	free(me);
}

int		del_parse(char **mas, int back)
{
	char **start;

	start = mas;
	while (*mas)
	{
		free(*mas);
		++mas;
	}
	free(start);
	return (back);
}

int		free_lst(t_lst *me, char stat)
{
	t_lst *next;

	while (me)
	{
		next = me->next;
		if (stat)
			free(me->one_line);
		free(me);
		me = next;
	}
	return (1);
}

int		free_nodes(t_node **me)
{
	t_node **i;

	i = me;
	while (*i)
	{
		free((*i)->name);
		free(*i);
		++i;
	}
	free(me);
	return (1);
}
