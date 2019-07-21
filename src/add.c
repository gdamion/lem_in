/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:42:33 by gdamion-          #+#    #+#             */
/*   Updated: 2019/06/30 16:42:37 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_elem(char **line, t_lst **lst)
{
	t_lst	*new;

	if (!(new = ft_memalloc(sizeof(t_lst))))
		project_free(ERR_ALLOC);
	new->line = *line;
	if (*lst)
		(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

void		add_room(char **table, t_rooms **rooms)
{
	t_rooms	*new;

	if (!(new = ft_memalloc(sizeof(t_rooms))))
		project_free(ERR_ALLOC);
	if (valid_name(table[0]))
		new->name = ft_strdup(table[0]);
	else
		project_free(ERR_ILLEGAL_NAME);
	new->x = is_integer(table[1]);
	new->y = is_integer(table[2]);
	free_words(&table);
	new->next = *rooms;
	*rooms = new;
}

void		add_link(char **table, t_links **links)
{
	t_links	*new;

	if (!(new = ft_memalloc(sizeof(t_links))))
		project_free(ERR_ALLOC);
	new->a = table[0];
	new->b = table[1];
	new->next = *links;
	*links = new;
}
