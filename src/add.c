#include "lem_in.h"

void		add_elem(char **line, t_lst **lst)
{
	t_lst	*new;

	new = ft_memalloc(sizeof(t_lst));
	new->line = *line;
	if (*lst)
		(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

void		add_room(char **table, t_rooms **rooms)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	if (valid_name(table[0]))
		new->name = table[0];
	else
		project_free(ERR_ILLEGAL_NAME);
	new->x = is_integer(table[1]);
	new->y = is_integer(table[2]);
	ft_strdel(&(table[1]));
	ft_strdel(&(table[2]));
	new->next = *rooms;
	*rooms = new;
}

void		add_link(char **table, t_links **links)
{
	t_links	*new;

	new = ft_memalloc(sizeof(t_links));
	new->a = table[0];
	new->b = table[1];
	new->next = *links;
	*links = new;
}
