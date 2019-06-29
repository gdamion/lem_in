#include "lem_in.h"

int			get_lenght(int i)
{
	int		from;
	int		len;
	int		to;

	from = i;
	len = 1;
	while (from != (g_lem_in->rooms - 1))
	{
		to = g_lem_in->rooms - 1;
		while (to >= 0)
		{
			if (g_np[from][to] == TRUE)
			{
				from = to;
				len++;
				break ;
			}
			to--;
		}
	}
	return (len);
}

void		update_ways(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_lem_in->rooms)
	{
		j = i;
		while (j >= 0)
		{
			if (g_np[i][j] == TRUE && TRUE == g_np[j][i])
			{
				g_np[i][j] = 0;
				g_np[j][i] = 0;
			}
			j--;
		}
		i++;
	}
}

int			perfomance(int sum_len, int ants, int n_paths)
{
	int steps;

	steps = (sum_len + ants) / n_paths - 1;
	if (!(ants % n_paths))
		return (steps);
	else
		return (steps + 1);
}

int			check_performance(void)
{
	int	i;
	int	sum_len;
	int	counter;

	i = 0;
	sum_len = 0;
	counter = 0;
	while (i < g_lem_in->rooms)
	{
		if (g_np[0][i] == TRUE)
		{
			sum_len += get_lenght(i);
			counter++;
		}
		i++;
	}
	return (perfomance(sum_len, g_lem_in->ants, counter));
}

void		find_ways(void)
{
	int		error;
	int		perf;
	int		min_perf;

	error = ERROR;
	g_np = init_matrix(g_lem_in->rooms);
	g_mnp = init_matrix(g_lem_in->rooms);
	min_perf = MAX_INT;
	while (error)
	{
		if (!find_paths())
			break ;
		update_ways();
		get_residual_network();
		perf = check_performance();
		if (perf < min_perf)
		{
			cpy_ways();
			min_perf = perf;
		}
		else
			error--;
	}
}
