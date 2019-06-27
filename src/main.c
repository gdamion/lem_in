#include "lem_in.h"

// void		clean_matrix(_Bool ***m)
// {
// 	int i;

// 	i = 0;
// 	while (i < g_lem_in->rooms)
// 		free((*m)[i++]);
// 	free(*m);
// }

// int			free_info(void)
// {
// 	if (g_np)
// 		clean_matrix(&g_np);
// 	if (g_mnp)
// 		clean_matrix(&g_mnp);
// 	ft_putendl("Error");
// 	if (g_lem_in)
// 	{
// 		free_lst(g_lem_in->data, 1);
// 		free_nodes(g_lem_in->nodes);
// 		clean_matrix(&g_lem_in->links);
// 		free(g_lem_in);
// 	}
// 	exit(0);
// }

// int	free_lem_in(void)
// {
// 	if (g_np)
// 		clean_matrix(&g_np);
// 	if (g_mnp)
// 		clean_matrix(&g_mnp);
// 	if (g_lem_in)
// 	{
// 		free_lst(g_lem_in->data, 1);
// 		free_nodes(g_lem_in->nodes);
// 		clean_matrix(&g_lem_in->links);
// 		free(g_lem_in);
// 	}
// 	return (1);
// }

int			main(int ac, char **av)
{
	// t_pathkit	p_kit;
	// t_lst		*p;

	(void)av;
	errno = 0;
	if (ac != 1)
		print_error("Error");
	g_np = NULL;
	g_mnp = NULL;
	g_lem_in = NULL;
	g_lem_in = anthill();
	// min_ways();
	// // p_kit = set_paths_kit();
	// p = g_lem_in->data;
	// while (p)
	// {
	// 	ft_printf("%s\n", p->line);
	// 	p = p->next;
	// }
	// ft_printf("\n");
	// // push_ants(p_kit, g_lem_in->ants);
	// free_lem_in();
	exit(0);
}
