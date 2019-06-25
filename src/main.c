#include "lem_in.h"

void		clean_matrix(_Bool ***m)
{
	int i;

	i = 0;
	while (i < g_info->n_rooms)
		free((*m)[i++]);
	free(*m);
}

int			error(void)
{
	if (g_np)
		clean_matrix(&g_np);
	if (g_mnp)
		clean_matrix(&g_mnp);
	ft_putendl("Error");
	if (g_info)
	{
		free_lst(g_info->data, 1);
		free_nodes(g_info->nodes);
		clean_matrix(&g_info->links);
		free(g_info);
	}
	exit(0);
}

static int	free_info(void)
{
	if (g_np)
		clean_matrix(&g_np);
	if (g_mnp)
		clean_matrix(&g_mnp);
	if (g_info)
	{
		free_lst(g_info->data, 1);
		free_nodes(g_info->nodes);
		clean_matrix(&g_info->links);
		free(g_info);
	}
	return (1);
}

int			main(void)
{
	t_pathkit	p_kit;
	t_lst		*p;

	g_info = NULL;
	g_info = read_map();
	g_np = NULL;
	g_mnp = NULL;
	find_mnp();
	p_kit = find_path_kit();
	p = g_info->data;
	while (p)
	{
		ft_printf("%s\n", p->one_line);
		p = p->next;
	}
	ft_putendl("");
	push_ants(p_kit, g_info->n_ants);
	free_info();
	exit(0);
}
