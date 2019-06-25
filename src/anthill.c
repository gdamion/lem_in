#include "lem_in.h"

static int	get_index(char *nom, char **names)
{
	int i;

	i = 0;
	while (names[i])
	{
		if (!ft_strcmp(names[i], nom))
			return (i);
		++i;
	}
	return (-1);
}

static int	fill_links(_Bool **links, t_lst *src, char **names, int n)
{
	int		l;
	int		ll;
	char	*pos;
	int		last;

	while (src)
	{
		pos = ft_strchr(src->one_line, '-');
		*pos = '\0';
		l = get_index(src->one_line, names);
		ll = get_index(pos + 1, names);
		*pos = '-';
		links[l][ll] = 1;
		links[ll][l] = 1;
		src = src->next;
	}
	l = 0;
	ll = 0;
	last = n - 1;
	while (n--)
	{
		l += links[0][n];
		ll += links[last][n];
	}
	return (l && ll);
}

static void	fill_nodes(t_node **nodes, t_lst *rms, char **names, t_valid *map)
{
	*names = ft_strsub(map->start, 0,
	ft_strchr(map->start, ' ') - map->start);
	*nodes = ft_memalloc(sizeof(t_node));
	(*nodes)->name = *(names++);
	(*(nodes++))->status = 0;
	while (rms)
	{
		if (ft_strcmp(rms->one_line, map->start) &&
		ft_strcmp(rms->one_line, map->end))
		{
			*nodes = ft_memalloc(sizeof(t_node));
			*names = ft_strsub(rms->one_line, 0,
			ft_strchr(rms->one_line, ' ') - rms->one_line);
			(*nodes)->name = *(names++);
			(*(nodes++))->status = 0;
		}
		rms = rms->next;
	}
	*names = ft_strsub(map->end, 0, ft_strchr(map->end, ' ') - map->end);
	*nodes = ft_memalloc(sizeof(t_node));
	(*nodes)->name = *names;
	(*nodes)->status = 0;
	*(++nodes) = NULL;
	*(++names) = NULL;
}

static int	convert(t_valid *map, t_lem_in *inf)
{
	int		p;
	_Bool	**lp;

	inf->nodes = ft_memalloc(sizeof(t_node*) * (map->num_r + 1));
	inf->links = ft_memalloc(sizeof(char*) * (map->num_r));
	map->names = ft_memalloc(sizeof(char*) * (map->num_r + 1));
	p = map->num_r;
	lp = inf->links;
	while (p)
	{
		*lp = ft_memalloc((map->num_r) * sizeof(_Bool));
		ft_bzero(*lp, (map->num_r) * sizeof(_Bool));
		--p;
		++lp;
	}
	fill_nodes(inf->nodes, map->rooms, map->names, map);
	if (!fill_links(inf->links, map->links, map->names, map->num_r))
		termination();
	inf->data = map->data;
	inf->rooms = map->num_r;
	return (1);
}

t_lem_in		*get_anthill(void)
{
	t_valid		*map;
	t_lem_in	*lem_in;
	char		*line;
	int			stat;

	if (!(lem_in = malloc(sizeof(t_lem_in))))
		termination();
	ft_bzero(lem_in, sizeof(t_lem_in));
	if (!(map = ft_memalloc(sizeof(t_valid))))
		termination();
	ft_bzero(map, sizeof(t_valid));
	while ((stat = get_next_line(0, &line)) > 0 && check_comment(line) > 0)
		push_elem(line, &map->data);
	if (stat < 1 || !is_int(line))
		termination();
	if ((lem_in->ants = ft_atoi(line)) < 1)
		termination();
	push_elem(line, &map->data);
	if (!read_data(map))
		termination();
	if (!convert(map, lem_in))
		termination();
	free_t_valid(map);
	return (lem_in);
}