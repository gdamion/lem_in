#include "lem_in.h"

void		add_elem(char *line, t_lst **lst)
{
	t_lst	*new;

	new = ft_memalloc(sizeof(t_lst));
	new->next = *lst;
	new->line = line;
	*lst = new;
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
