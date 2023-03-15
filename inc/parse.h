#ifndef PARSE_H
# define PARSE_H

enum e_room_type
{
	START = 0,
	END = 1,
	NORMAL = 2,
	LINK = 3,
	COMMENT = 4,
	ERROR = 5,
};

int	parser_read_data(t_list *list, char *buf);

/*
 *	Room Functions
*/
int		add_room(t_list *list, char *name, int x, int y);
t_room	*last_room(t_list *list);
t_room	*find_room(t_room* head, char *find);



#endif