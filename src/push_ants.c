/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:43:32 by gdamion-          #+#    #+#             */
/*   Updated: 2019/06/30 16:43:32 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ants_distribution(t_pathkit paths, int ants)
{
	int		i;
	int		j;
	int		sum;
	int		steps;

	j = 0;
	sum = 0;
	while (j < paths.len)
		sum += paths.paths[j++].len;
	steps = ((sum + ants) / paths.len) - 1;
	i = 0;
	sum = 0;
	while (i < paths.len)
	{
		paths.paths[i].ants = steps - paths.paths[i].len + 1;
		sum += paths.paths[i++].ants;
	}
	ants -= sum;
	while (ants > 0)
		paths.paths[ants-- - 1].ants++;
}

static void	set_squads(t_pathkit paths)
{
	int		i;
	int		interval;

	i = 0;
	interval = 1;
	while (i < paths.len)
	{
		paths.paths[i].index = interval;
		interval += paths.paths[i++].ants;
	}
}

static void	push_squads(t_pathkit paths)
{
	int		i;
	int		move;
	int		limit;

	move = 1;
	limit = paths.paths[0].len + paths.paths[0].ants - 1;
	while (move <= limit)
	{
		i = -1;
		while (++i < paths.len)
			print_steps(paths, move, i, paths.paths[i].index);
		ft_printf("\n");
		move++;
	}
}

void		push_ants(t_pathkit paths, int ants)
{
	ants_distribution(paths, ants);
	set_squads(paths);
	push_squads(paths);
}
