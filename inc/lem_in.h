/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdamion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:44:31 by gdamion-          #+#    #+#             */
/*   Updated: 2019/06/30 16:57:44 by gdamion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <errno.h>

/*
** Lem-in message
*/

# define LEM_IN_USAGE			"Usage: ./lem-in < MAP_FILE"
# define ERR_LEM_IN_INIT		"ERROR: Can\'t initialize Lem-in"

/*
** Types of error
*/

# define ERR_LINKS				"ERROR: Invalid link(s)"
# define ERR_NO_LINKS			"ERROR: Links is absent"
# define ERR_READING			"ERROR: Reading error"
# define ERR_NUM_ANTS			"ERROR: Invalid number of ants"
# define ERR_END_ROOM			"ERROR: More than 1 \"end\" room"
# define ERR_LINE_INIT			"ERROR: Can\'t initialize line"
# define ERR_MATRIX_INIT		"ERROR: Can\'t initialize matrix"
# define ERR_START_ROOM			"ERROR: More than 1 \"start\" room"
# define ERR_ROOM_PARSING		"ERROR: Reading rooms"
# define ERR_ILLEGAL_NAME		"ERROR: Illegal name"
# define ERR_LINK_DUPLICATE		"ERROR: The duplication link"
# define ERR_ROOM_DUPLICATE		"ERROR: The duplication room"
# define ERR_START_END_ROOM		"ERROR: No \"start\" or \"end\" room(s)"

/*
** Properties
*/

# define ERROR 5
# define TRUE 1
# define FALSE 0
# define STATUS(i) (g_lem_in->status[i])
# define PATHS() ((t_path*)malloc(sizeof(t_path) * p_kit.len))
# define INIT_LEM_IN (!(g_lem_in = (t_lem_in *)ft_memalloc(sizeof(t_lem_in))))

/*
** Working structures
*/

typedef struct			s_lst
{
	char				*line;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

typedef struct			s_links
{
	char				*a;
	char				*b;
	struct s_links		*next;
}						t_links;

typedef struct			s_rooms
{
	int					x;
	int					y;
	char				*name;
	struct s_rooms		*next;
}						t_rooms;

typedef	struct			s_lem_in
{
	int					end;
	int					ants;
	int					start;
	int					rooms;
	char				**names;
	char				*status;
	_Bool				**matrix;
	t_rooms				*nodes;
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

/*
** Global variables
*/

t_lem_in				*g_lem_in;
_Bool					**g_np;
_Bool					**g_mnp;

/*
** Functions of the main program
*/

void					init_lem();
t_lem_in				*get_anthill(void);
_Bool					is_comment(char *str);
_Bool					is_command(char *str);
_Bool					is_link(char *str);
_Bool					is_int(const char *str, _Bool strict);
int						is_integer(char *s);
size_t					row_count(char **table);
_Bool					valid_name(char *str);

_Bool					get_room(t_lem_in *lem_in, char *str);
_Bool					get_command(t_lem_in *lem_in, char *str);
_Bool					get_link(t_lem_in *lem_in, char *str);
void					add_room(char **table, t_rooms **rooms);
void					add_link(char **table, t_links **links);
void					rooms_duplicate(t_rooms *nodes);
char					**set_names(t_lem_in *lem_in, t_rooms **nodes);

void					output(t_lst **data);
int						project_free(char *massage);
void					clean_matrix(_Bool ***m);

_Bool					is_int(const char *str, _Bool strict);
int						check_comment(char *s);
int						link_ok(char *line, t_lst *rms, t_lst *links);
int						room_exist(char *line, t_lst *list, int stat);

void					add_elem(char **line, t_lst **lst);
void					push_elem(char *line, t_lst **lst);

t_lem_in				*get_anthill(void);

int						del_parse(char **mas, int back);
int						free_lst(t_lst *me, char stat);

int						find_paths(void);
void					find_ways(void);
int						check_performance(void);
int						perfomance(int sum_len, int ants, int n_paths);
void					update_ways(void);
int						get_lenght(int i);

void					get_residual_network(void);
void					set_path(t_room *path);
void					cpy_ways(void);
_Bool					**init_matrix(int rooms);

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

#endif
