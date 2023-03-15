#include "header.h"


/*
** A function to see if the ant in the current room
*/
int	is_ant_in_room(t_list *list, t_room *room)
{
	int	i = 0;
	t_ant *ants;

	while (&ants[i] != NULL)
	{
		if (ft_strncmp(ants[i].current_room, room->name, ft_strlen(room->name)) == 0)
			return (1);
		i++;
	}
	return (0);
}
