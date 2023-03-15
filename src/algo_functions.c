#include "header.h"


/*
** A function to find the ant closest to the end
*/
int	get_furthest_ant(t_list *list, t_room *room, int far)
{
	int	i, shortest;
	t_room *temp;

	if (!room->is_end || is_ant_in_room(list, room))
		return (far);

	i = 0;
	shortest = -1;
	while (temp->links[i])
	{
		temp = get_furthest_ant(list, find_room(list->rooms, temp->links[i]), far + 1);
		if (shortest == -1 || temp < shortest)
			shortest = temp;
		i++;
	}

	return (shortest);
}
