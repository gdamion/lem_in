#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

# define ERROR 5
# define TRUE 1
# define FALSE 0
# define STATUS(i) (g_lem_in->nodes[i]->status)
# define PATHS() ((t_path*)malloc(sizeof(t_path) * p_kit.len))

typedef struct			s_lst
{
	struct s_lst		*next;
	char				*one_line;
}						t_lst;

typedef struct			s_valid
{
	char				*start;
	char				*end;
	t_lst				*rooms;
	t_lst				*links;
	t_lst				*data;
	char				**names;
	int					num_r;
	int					num_l;
}						t_valid;

typedef struct			s_node
{
	char				*name;
	_Bool				status;
}						t_node;

typedef	struct			s_lem_in
{
	int					ants;
	int					rooms;
	t_node				**nodes;
	_Bool				**links;
	t_lst				*data;
}						t_lem_in;

typedef struct			s_room
{
	int					id;
	int					from;
	struct s_room		*next;
	struct s_room		*prev;
}						t_room;

typedef struct			s_path
{
	int					ants;
	int					index;
	int					len;
	int					*room;
}						t_path;

typedef struct			s_pathkit
{
	int					len;
	t_path				*paths;
}						t_pathkit;

typedef struct			s_id
{
	int					id;
	struct s_id			*next;
}						t_id;

int						termination();
int						is_int(char *s);
int						check_comment(char *s);
int						link_ok(char *line, t_lst *rms, t_lst *links);
int						room_exist(char *line, t_lst *list, int stat);

void					add_elem(char *line, t_lst **lst);
void					push_elem(char *line, t_lst **lst);

t_lem_in				*get_anthill(void);
int						read_data(t_valid *map);

void					free_t_valid(t_valid *me);
int						del_parse(char **mas, int back);
int						free_lst(t_lst *me, char stat);
int						free_nodes(t_node **me);

void					min_ways(void);
int						check_performance(void);
int						perfomance(int sum_len, int ants, int n_paths);
void					update_ways(void);
int						get_lenght(int i);

int						find_ways(void);
void					get_residual_network(void);
void					set_path(t_room *path);
void					cpy_ways(void);
_Bool					**init_ways(void);

t_room					*find_path(int i, int j);
_Bool					cross(int prev, int for_check);
t_room					*record_path(t_room *q);

t_room					*init_queue(int new_id, int prev_id, t_room *prev);
_Bool					queue_pop(t_room **q);
void					q_push(t_room *q, int new_id, int prev_id);
_Bool					if_q_empty(t_room *q, int id);

t_pathkit				set_paths_kit(void);
void					fill(t_pathkit *p_kit, t_id **l_id, int *i);
int						path_len(int i, t_id *l_id);
int						count_ways(void);

void					push_ants(t_pathkit paths, int ants);
void					push_squads(t_pathkit paths);
void					set_squads(t_pathkit paths);
void					ants_distribution(t_pathkit paths, int ants);

void					print_steps(t_pathkit paths, int move, int id, \
													int ants_start);

t_lem_in	*g_lem_in;
_Bool	**g_np;
_Bool	**g_mnp;

#endif
