#include "lem_in.h"

int			get_lenght(int i)
{
	int		from;
	int		len;
	int		to;

	from = i;
	len = 1;
	while (from != (g_info->n_rooms - 1))
	{
		to = g_info->n_rooms - 1;
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

void		suurballe_clean(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_info->n_rooms)
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

int			perfomance_formula(int sum_len, int n_ants, int n_paths)
{
	int steps;

	steps = (sum_len + n_ants) / n_paths;
	if (n_ants % n_paths)
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
	while (i < g_info->n_rooms)
	{
		if (g_np[0][i] == TRUE)
		{
			sum_len += get_lenght(i);
			counter++;
		}
		i++;
	}
	return (perfomance_formula(sum_len, g_info->n_ants, counter));
}

void		find_mnp(void)
{
	int		error;
	int		performance;
	int		min_performance;

	error = ERROR;
	g_np = np_init();
	g_mnp = np_init();
	min_performance = MAX_INT;
	while (error)
	{
		if (!find_np())
			break ;
		suurballe_clean();
		get_residual_network();
		performance = check_performance();
		if (performance < min_performance)
		{
			np_cpy();
			min_performance = performance;
		}
		else
			error--;
	}
}
