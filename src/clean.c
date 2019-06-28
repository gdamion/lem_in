#include "lem_in.h"

void		clean_matrix(_Bool ***m)
{
	int i;

	i = 0;
	if (!(m && *m))
		return ;
	while (i < g_lem_in->rooms)
		free((*m)[i++]);
	free(*m);
}

int			project_free(char *massage)
{
	if (g_np)
		clean_matrix(&g_np);
	if (g_mnp)
		clean_matrix(&g_mnp);
	if (g_lem_in)
	{
		clean_matrix(&g_lem_in->matrix);
		free_words(&g_lem_in->names);
		ft_strdel(&g_lem_in->status);
		free(g_lem_in);
	}
	if (massage)
		print_error(massage);
	exit(0);
}
