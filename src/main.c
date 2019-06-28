#include "lem_in.h"

int			main(int ac, char **av)
{
	t_pathkit	p_kit;

	(void)av;
	g_np = 0;
	g_mnp = 0;
	errno = 0;
	if (ac != 1)
		print_error("Error");
	get_anthill();
	find_ways();
	p_kit = set_paths_kit();
	output(&g_lem_in->data);
	push_ants(p_kit, g_lem_in->ants);
	project_free(0);
	exit(0);
}
