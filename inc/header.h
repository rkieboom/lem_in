#ifndef HEADER_H
# define HEADER_H

# include "../libft/inc/libft.h"

typedef struct	s_ant
{
	int				id;

	//The room that it is in
	char			*current_room;

	//The room it wants to go next
	char			*next_room;
}				t_ant;

typedef struct	s_room
{
	//Name of the room
	char			*name;

	//Coordinates of the room
	int				x;
	int				y;

	//Room linked to
	char			**links;

	//If the room is a start / end room
	int				is_start;
	int				is_end;

	struct s_room	*next;
}				t_room;

typedef struct	s_list
{
	t_ant			*ants;
	t_room			*rooms;

	unsigned int	ants_amount;
}				t_list;

int		parser(t_list *list);



/*
** Room Functions
*/
t_room *get_start_room(t_room *rooms);
t_room *get_end_room(t_room *rooms);
t_room	*find_room(t_room* head, char *find);


/*
** Ant Functions
*/
int	is_ant_in_room(t_list *list, t_room *room);

#endif