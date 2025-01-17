/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:43:27 by gdamion-          #+#    #+#             */
/*   Updated: 2019/06/30 16:44:01 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		squad_length(t_pathkit paths, int move, int id, int ants)
{
	if (move <= ants)
		return (move > paths.paths[id].len ? paths.paths[id].len : move);
	if (move <= paths.paths[id].len)
		return (ants);
	return (ants - move + paths.paths[id].len);
}

static int		get_start(int move, int ants)
{
	if (move <= ants)
		return (1);
	return (move - ants + 1);
}

void			print_steps(t_pathkit paths, int move, int id, int ants_start)
{
	int		start_room;
	int		end_room;
	int		ants_end;
	int		squad;

	start_room = get_start(move, paths.paths[id].ants);
	squad = squad_length(paths, move, id, paths.paths[id].ants);
	end_room = start_room + squad - 1;
	if (move > paths.paths[id].len)
		ants_start += move - paths.paths[id].len;
	ants_end = ants_start + squad - 1;
	while (ants_start <= ants_end)
		ft_printf("L%d-%s ", ants_start++,
		g_lem_in->names[paths.paths[id].room[end_room-- - 1]]);
}
